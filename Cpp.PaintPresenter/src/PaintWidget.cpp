#include "PaintWidget.hpp"

#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>

#include <poppler/qt5/poppler-qt5.h>

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
    , overlayImage_(size(), QImage::Format_ARGB32)
{
    drawPdf_ = false;
    pdfCurrentPage_ = 0;
    pdfDocument_ = nullptr;

    paintTool_ = PaintToolType::Pen;

    //this->setMouseTracking(true);
    pen_.setColor(QColor(255,0,0));
    pen_.setWidth(3);
    pen_.setStyle(Qt::SolidLine);
    pen_.setCapStyle(Qt::RoundCap);
    pen_.setJoinStyle(Qt::RoundJoin);

    isPainting_ = false;

    //alpha overlay
    overlayImage_.fill(QColor::fromRgb(0,0,0,0));
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
    overlayImage_.fill(QColor::fromRgb(0,0,0,0));
    this->update();
}

void PaintWidget::setPenColor(const QColor &color)
{
    pen_.setColor(color);
}

void PaintWidget::setPenWidth(int penWidth)
{
    //clamp to 1-10
    int penWidthNew = penWidth < 0 ? 1 : pen_.width() > 10 ? 10 : pen_.width();
    pen_.setWidth(penWidthNew);
}

void PaintWidget::setTool(PaintToolType tool)
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
    updatePdfPageImage();

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
    updatePdfPageImage();
    clearDrawOverlay();
    this->update();
}

void PaintWidget::prevPdfPage()
{
    if(pdfDocument_ == nullptr)
        return;

    pdfCurrentPage_ = clamp<int>(pdfCurrentPage_ - 1, 0, pdfDocument_->numPages()-1);
    updatePdfPageImage();
    clearDrawOverlay();
    this->update();
}

void PaintWidget::paintTo(const QRect &dirtyRect, QPainter &painter)
{
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
    painter.scale( (qreal)size.width() / (qreal)overlayImage_.width(), (qreal)size.height() / (qreal)overlayImage_.height());
    painter.drawImage(dirtyRect, overlayImage_, dirtyRect);

    //draw temporary stuff
    if(isPainting_ && paintTool_ == PaintToolType::Rectangle)
    {
       QColor color(pen_.color());
       color.setAlpha(100);
       painter.fillRect(rectTool, color);
    }

    painter.restore();
}

// update the pdf image
void PaintWidget::updatePdfPageImage()
{
    if(pdfDocument_ == nullptr)
        return;

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
     paintTo(dirtyRect, painter);
}

void PaintWidget::resizeEvent(QResizeEvent* event)
{
    //when auto-size is enabled set the "output" size to the current paint widget size
    if(autoOutputSize_)
        updateOutputSize(this->size());

    QWidget::resizeEvent(event);
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{

    if ((event->buttons() & Qt::LeftButton) && isPainting_)
    {
        //TODO calculate mouse position

        switch(paintTool_)
        {
        case PaintToolType::Pen:
            drawLineTo(event->pos());
            break;
        case PaintToolType::Highlight:
        {
            QPoint p = event->pos();
            p.setY(penLastPoint_.y());
            drawLineTo(p);
            break;
        }
        case PaintToolType::Rectangle:
            rectTool.setWidth(event->x()-rectTool.x());
            rectTool.setHeight(event->y()-rectTool.y());
            this->update();
            break;
        case PaintToolType::Text:
            break;
        case PaintToolType::Erease:
            break;
        }
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        //TODO calculate mouse position

        switch(paintTool_)
        {
        case PaintToolType::Pen:
            penLastPoint_ = event->pos();
            break;
        case PaintToolType::Highlight:
            penLastPoint_ = event->pos();
            break;
        case PaintToolType::Rectangle:
            rectTool.setX(event->x());
            rectTool.setY(event->y());
            break;
        case PaintToolType::Text:
            break;
        case PaintToolType::Erease:
            break;
        }
        isPainting_ = true;
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && isPainting_)
    {
        //TODO calculate mouse position

        switch(paintTool_)
        {
        case PaintToolType::Pen:
            drawLineTo(event->pos());
            break;
        case PaintToolType::Highlight:
        {
            QPoint p = event->pos();
            p.setY(penLastPoint_.y());
            drawLineTo(p);
            break;
        }
        case PaintToolType::Rectangle:
        {
            overlayPainter_.begin(&overlayImage_);
            QColor color(pen_.color());
            color.setAlpha(100);
            overlayPainter_.fillRect(rectTool, color);
            overlayPainter_.end();
            break;
        }
        case PaintToolType::Text:
            break;
        case PaintToolType::Erease:
            break;
        }
        isPainting_ = false;
    }
}


void PaintWidget::drawLineTo(const QPoint &endPoint)
{
    int width =  paintTool_ == PaintToolType::Highlight ? 30 : pen_.width();

    if(overlayImage_.isNull())
        std::cout << "Null image" << std::endl;

    overlayPainter_.begin(&overlayImage_);
    overlayPainter_.setPen(pen_);
    if(paintTool_ == PaintToolType::Highlight)
    {
        QColor color(pen_.color());
        color.setAlpha(100);
        overlayPainter_.setPen(QPen(color, width, Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin));
    }
    overlayPainter_.drawLine(penLastPoint_, endPoint);
    overlayPainter_.end();

    //modified = true;

    int rad = (width / 2) + 2;

    QRect dirtyRect = QRect(penLastPoint_, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad);
    this->update(dirtyRect);
    emit drawingsChanged(dirtyRect);
    penLastPoint_ = endPoint;
}

// set the "output" size of the data
// update overlay format and pdf image
void PaintWidget::updateOutputSize(const QSize& size)
{
    std::cout << "size: " << size.width() << " " << size.height() << std::endl;

    //set the output size
    outputSize_ = size;

    //overlay stuff
    overlayImage_ = overlayImage_.scaled(outputSize_.width(), outputSize_.height());

    //Iterate over all current overlay images

    //setup pdf image
    updatePdfPageImage();

    //repaint
    this->update();
}
