
#include "PaintTool.hpp"

#include <QMouseEvent>

PaintTool::PaintTool(const QPen& pen)
    : pen_(pen)
{

}

PaintTool::~PaintTool()
{

}


void PaintTool::mouseMoveEvent(QMouseEvent*, QPainter&)
{

}

void PaintTool::mousePressEvent(QMouseEvent* , QPainter&)
{

}

void PaintTool::mouseReleaseEvent(QMouseEvent* , QPainter&)
{

}

//--------------------------------------------------------------------------------------------------

PenTool::PenTool(const QPen &pen)
    : PaintTool(pen)
{

}

PenTool::~PenTool()
{

}

void PenTool::mouseMoveEvent(QMouseEvent *event, QPainter& p)
{
	//todo calculate right mouse position

	drawLineTo(p, event->pos());
}

void PenTool::mousePressEvent(QMouseEvent *event, QPainter& p)
{
	penLastPoint_ = event->pos();
}

void PenTool::mouseReleaseEvent(QMouseEvent *event, QPainter& p)
{
	drawLineTo(p, event->pos());
}

void PenTool::drawLineTo(QPainter& p, const QPoint& endPoint)
{
	p.setPen(pen_);
	p.drawLine(penLastPoint_, endPoint);

	//int rad = (pen_.width()/ 2) + 2;
	//QRect dirtyRect = QRect(penLastPoint_, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad);

	penLastPoint_ = endPoint;

	//emit change event?
}
