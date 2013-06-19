#include "paintwidget.h"

#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>

#include <iostream>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , image_(size(), QImage::Format_ARGB32)
{

    paintTool_ = PaintTool::Pen;

    //this->setMouseTracking(true);
    penColor_.setRgb(255,0,0);
    penWidth_ = 3;
    isPainting_ = false;

    image_.fill(QColor::fromRgb(0,0,0,0));
}

void PaintWidget::makeScreenshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        screenhot_ = screen->grabWindow(0);
        drawScreenhot_ = true;
        this->update();
    }
}

void PaintWidget::clearScreenshot()
{
    drawScreenhot_ = false;
    this->update();
}

void PaintWidget::clearDrawings()
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

void PaintWidget::paintEvent(QPaintEvent* event)
{
     QRect dirtyRect = event->rect();

     QPainter painter(this);
     //draw screenshot if enabled
     if(drawScreenhot_)
     {
        //scale keep dimensions
        //draw in center
        //scale right?
        painter.drawPixmap(dirtyRect, screenhot_, dirtyRect);
     }

     //draw the draw image
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
}

void PaintWidget::resizeEvent(QResizeEvent* event)
{

    //std::cout << "resize" << std::endl;
    auto size = this->size();
    image_ = image_.scaled(size.width(), size.height());


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
            painter_.begin(&image_);
            QColor color(penColor_);
            color.setAlpha(100);
            painter_.fillRect(rectTool, color);
            painter_.end();
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
