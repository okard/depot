
#include "PaintTool.hpp"


PaintTool::PaintTool(const QPen& pen)
    : pen_(pen)
{

}

PaintTool::~PaintTool()
{

}


void PaintTool::mouseMoveEvent(QMouseEvent *event)
{

}

void PaintTool::mousePressEvent(QMouseEvent *event)
{

}

void PaintTool::mouseReleaseEvent(QMouseEvent *event)
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

void PenTool::mouseMoveEvent(QMouseEvent *event)
{
    //drawLineTo(event->pos());
}

void PenTool::mousePressEvent(QMouseEvent *event)
{
    //penLastPoint_ = event->pos();
}

void PenTool::mouseReleaseEvent(QMouseEvent *event)
{
    //drawLineTo(event->pos());
}
