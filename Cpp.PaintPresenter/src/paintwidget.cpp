#include "paintwidget.h"

#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>

#include <iostream>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , image_(size(), QImage::Format_ARGB32)
{

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
            drawLineTo(event->pos());

}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        lastPoint_ = event->pos();
        isPainting_ = true;
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && isPainting_)
    {
           drawLineTo(event->pos());
           isPainting_ = false;
    }
}


void PaintWidget::drawLineTo(const QPoint &endPoint)
{
    painter_.begin(&image_);
    painter_.setPen(QPen(penColor_, penWidth_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter_.drawLine(lastPoint_, endPoint);
    painter_.end();

    //modified = true;

    int rad = (penWidth_ / 2) + 2;
    this->update(QRect(lastPoint_, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint_ = endPoint;
}
