#include "paintwidget.h"

#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>

#include <poppler-qt5.h>

#include <iostream>


static QRect calcDrawArea(const QSize& source, const QSize& target)
{
    QSize s = source;
    s.scale(target.width(), target.height(), Qt::KeepAspectRatio);
    int x = s.width() < target.width() ? (qreal)(target.width() - s.width())/(qreal)2 : 0;
    int y = s.height() < target.height() ? (qreal)(target.height() - s.height())/(qreal)2 : 0;
    return QRect(x, y, s.width(), s.height());
}

template<typename T>
static inline T clamp(T value, T min, T max)
{
    return value > max ? max : value < min ? min : value;
}



PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , image_(size(), QImage::Format_ARGB32)
{
    drawPdf_ = false;
    pdfCurrentPage_ = 0;
    pdfDocument_ = nullptr;

    paintTool_ = PaintTool::Pen;

    //this->setMouseTracking(true);
    penColor_.setRgb(255,0,0);
    penWidth_ = 3;
    isPainting_ = false;

    //alpha overlay
    image_.fill(QColor::fromRgb(0,0,0,0));
}

PaintWidget::~PaintWidget()
{
    closePdfFile();
}

void PaintWidget::makeScreenshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        screenshot_ = screen->grabWindow(0);

        //std::cout << "screenshot: " << screenshot_.width()<< "," << screenshot_.height() << std::endl;
        drawScreenhot_ = true;
        this->update();
    }
}

void PaintWidget::clearScreenshot()
{
    drawScreenhot_ = false;
    this->update();
}

void PaintWidget::clearDrawOverlay()
{
    image_.fill(QColor::fromRgb(0,0,0,0));
    this->update();
}

void PaintWidget::setPenColor(const QColor &color)
{
    penColor_ = color;
}

void PaintWidget::setPenWidth(int penWidth)
{
    //clamp to 1-10
    penWidth_ = penWidth < 0 ? 1 : penWidth_ > 10 ? 10 : penWidth_;
}

void PaintWidget::setTool(PaintTool tool)
{
    //finish current action?
    if(isPainting_)
    {
        isPainting_ = false;
    }

    paintTool_ = tool;
}

void PaintWidget::openPdfFile(const QString &filename)
{
    Poppler::Document *newdoc = Poppler::Document::load(filename);

    if (!newdoc)
    {
            QMessageBox msgbox(QMessageBox::Critical, tr("Open Error"), tr("Cannot open:\n") + filename, QMessageBox::Ok, this);
            msgbox.exec();
            return;
    }


    closePdfFile();

    pdfDocument_ = newdoc;
    pdfCurrentPage_ = 0;
    pdfDocument_ ->setRenderHint(Poppler::Document::TextAntialiasing, true);
    pdfDocument_ ->setRenderHint(Poppler::Document::Antialiasing, true);
    pdfDocument_->setRenderBackend(Poppler::Document::SplashBackend);

    drawPdf_ = true;

    //initial pdf image
    makePdfImage();

}

void PaintWidget::closePdfFile()
{
    if(pdfDocument_)
    {
        delete pdfDocument_;
        pdfDocument_ = nullptr;
        pdfCurrentPage_ = 0;
    }
    drawPdf_ = false;
}

void PaintWidget::nextPdfPage()
{
    if(pdfDocument_ == nullptr)
        return;

    pdfCurrentPage_ = clamp<int>(pdfCurrentPage_ + 1, 0, pdfDocument_->numPages()-1);
    makePdfImage();
    clearDrawOverlay();
    this->update();
}

void PaintWidget::prevPdfPage()
{
    if(pdfDocument_ == nullptr)
        return;

    pdfCurrentPage_ = clamp<int>(pdfCurrentPage_ - 1, 0, pdfDocument_->numPages()-1);
    makePdfImage();
    clearDrawOverlay();
    this->update();
}

void PaintWidget::makePdfImage()
{
    //TODO calculate right dpi for output size
    auto page = pdfDocument_->page(pdfCurrentPage_);
    auto size = page->pageSize(); //page size in points, 72 dpi == each point one pixel
    auto rect = calcDrawArea(size, outputSize_); //scale up to size
    //extract factor
    float xfactor = 72.0 * ((qreal)rect.width()/(qreal)size.width());
    float yfactor = 72.0 * ((qreal)rect.height()/(qreal)size.height());
    pdfImage_  = page->renderToImage(xfactor, yfactor);
    delete page;
}

void PaintWidget::paintEvent(QPaintEvent* event)
{
     QRect dirtyRect = event->rect();

     QPainter painter(this);

     painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
     painter.setRenderHint(QPainter::Antialiasing, true);
     //painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

     //draw screenshot if enabled
     if(drawScreenhot_)
     {
        painter.save();

        auto size = painter.viewport().size();
        QSize s = screenshot_.size();
        QRect r = calcDrawArea(s, size);

        painter.drawPixmap(r,screenshot_);
        painter.restore();
     }

     //draw pdf if available
     if(drawPdf_ && pdfDocument_)
     {
        QSize s(4, 3);
        QRect area = calcDrawArea(s, painter.viewport().size());
        //std::cout << area.x() << ' ' << area.y() << ' ' << area.width() << ' ' << area.height() << std::endl;
        painter.drawImage(area, pdfImage_);
     }

     painter.save();
     //draw the overlay image
     auto size = this->size();
     painter.scale( (qreal)size.width() / (qreal)image_.width(), (qreal)size.height() / (qreal)image_.height());
     painter.drawImage(dirtyRect, image_, dirtyRect);

     //draw temporary stuff
     if(isPainting_ && paintTool_ == PaintTool::Rectangle)
     {
        QColor color(penColor_);
        color.setAlpha(100);
        painter.fillRect(rectTool, color);
     }
     painter.restore();
}

void PaintWidget::resizeEvent(QResizeEvent* event)
{
    outputSize_ = this->size();
    image_ = image_.scaled(outputSize_.width(), outputSize_.height());

    QWidget::resizeEvent(event);
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{

    if ((event->buttons() & Qt::LeftButton) && isPainting_)
    {
        switch(paintTool_)
        {
        case PaintTool::Pen:
            drawLineTo(event->pos());
            break;
        case PaintTool::Highlight:
        {
            QPoint p = event->pos();
            p.setY(penLastPoint_.y());
            drawLineTo(p);
            break;
        }
        case PaintTool::Rectangle:
            rectTool.setWidth(event->x()-rectTool.x());
            rectTool.setHeight(event->y()-rectTool.y());
            this->update();
            break;
        case PaintTool::Text:
            break;
        case PaintTool::Erease:
            break;
        }
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {

        switch(paintTool_)
        {
        case PaintTool::Pen:
            penLastPoint_ = event->pos();
            break;
        case PaintTool::Highlight:
            penLastPoint_ = event->pos();
            break;
        case PaintTool::Rectangle:
            rectTool.setX(event->x());
            rectTool.setY(event->y());
            break;
        case PaintTool::Text:
            break;
        case PaintTool::Erease:
            break;
        }
        isPainting_ = true;
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && isPainting_)
    {
        switch(paintTool_)
        {
        case PaintTool::Pen:
            drawLineTo(event->pos());
            break;
        case PaintTool::Highlight:
        {
            QPoint p = event->pos();
            p.setY(penLastPoint_.y());
            drawLineTo(p);
            break;
        }
        case PaintTool::Rectangle:
        {
            painter_.begin(&image_);
            QColor color(penColor_);
            color.setAlpha(100);
            painter_.fillRect(rectTool, color);
            painter_.end();
            break;
        }
        case PaintTool::Text:
            break;
        case PaintTool::Erease:
            break;
        }
        isPainting_ = false;
    }
}


void PaintWidget::drawLineTo(const QPoint &endPoint)
{
    int width =  paintTool_ == PaintTool::Highlight ? 20 : penWidth_;

    painter_.begin(&image_);
    painter_.setPen(QPen(penColor_, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if(paintTool_ == PaintTool::Highlight)
    {
        QColor color(penColor_);
        color.setAlpha(100);
        painter_.setPen(QPen(color, width, Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin));
    }
    painter_.drawLine(penLastPoint_, endPoint);
    painter_.end();

    //modified = true;

    int rad = (width / 2) + 2;
    this->update(QRect(penLastPoint_, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    penLastPoint_ = endPoint;
}
