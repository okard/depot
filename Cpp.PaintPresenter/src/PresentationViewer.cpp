#include "PresentationViewer.hpp"



PresentationViewer::PresentationViewer(QQuickItem *parent) :
    QQuickItem(parent)
{
    //this->setMouseTracking(true);
    pen_.setColor(QColor(255,0,0));
    pen_.setWidth(3);
    pen_.setStyle(Qt::SolidLine);
    pen_.setCapStyle(Qt::RoundCap);
    pen_.setJoinStyle(Qt::RoundJoin);

    tools_.insert(std::make_pair<PaintToolType, std::unique_ptr<PaintTool>>(Pen, std::unique_ptr<PaintTool>(new PenTool(pen_))));
}

void PresentationViewer::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMove(event);
}

void PresentationViewer::mousePressEvent(QMouseEvent *event)
{
    emit mousePress(event);
}

void PresentationViewer::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseRelease(event);
}

void PresentationViewer::switchTool(PresentationViewer::PaintToolType t)
{
    if(currentTool_ != nullptr)
    {
        //disconnect events
        currentTool_->disconnect();
        currentTool_ = nullptr;
    }

    currentTool_ = tools_[t].get();
    connect(this, SIGNAL(mouseMove), currentTool_, SLOT(mouseMoveEvent));
    connect(this, SIGNAL(mousePress), currentTool_, SLOT(mousePressEvent));
    connect(this, SIGNAL(mouseRelease), currentTool_, SLOT(mouseReleaseEvent));

    //connect events
}
