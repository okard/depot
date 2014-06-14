#include "PresentationViewer.hpp"

#include <QPainter>

#include "Helper.hpp"

PresentationViewer::PresentationViewer(QQuickItem *parent) :
	QQuickPaintedItem(parent), view_(nullptr)
{
    //this->setMouseTracking(true);
    pen_.setColor(QColor(255,0,0));
    pen_.setWidth(3);
    pen_.setStyle(Qt::SolidLine);
    pen_.setCapStyle(Qt::RoundCap);
    pen_.setJoinStyle(Qt::RoundJoin);

	tools_.insert(std::make_pair<PaintToolType, std::unique_ptr<PaintTool>>(Pen, std::unique_ptr<PaintTool>(new PenTool(pen_))));


	setFlag(QQuickItem::ItemHasContents);
	setAcceptedMouseButtons(Qt::AllButtons);
}

void PresentationViewer::mouseMoveEvent(QMouseEvent *event)
{
	//only fire tool events when required
	if(view_ != nullptr && view_->hasOverlay())
	{
		overlayPainter_.begin(view_->get_overlay());
		emit mouseMove(event, overlayPainter_);
		overlayPainter_.end();
		update();
	}
}

void PresentationViewer::mousePressEvent(QMouseEvent *event)
{
	qDebug() << "PresentationViewer::mousePressEvent called";

	//create overlay when not available
	if( view_ != nullptr
	&& currentTool_ != nullptr
	&& !view_->hasOverlay())
	{
		view_->createOverlay();
	}

	//only fire tool events when required
	if(view_ != nullptr && view_->hasOverlay())
	{
		QPointF pos = translatePoint(event->pos(), view_->get_overlay()->rect(), boundingRect());

		overlayPainter_.begin(view_->get_overlay());
		emit mousePress(event, overlayPainter_);
		overlayPainter_.end();
		update();
	}
}

void PresentationViewer::mouseReleaseEvent(QMouseEvent *event)
{
	//only fire tool events when required
	if(view_ != nullptr && view_->hasOverlay())
	{
		overlayPainter_.begin(view_->get_overlay());
		emit mouseRelease(event, overlayPainter_);
		overlayPainter_.end();
		update();
	}
}

View* PresentationViewer::get_view()
{
	return view_;
}

void PresentationViewer::set_view(View* v)
{
	if(v == nullptr)
		return;

	if(view_ != nullptr)
	{
		disconnect(view_, &View::view_changed, this, &PresentationViewer::redraw );
		view_ = nullptr; //reset internal view
	}

	//overlayPainter_ = QPainter();

	qDebug() << "PresentationViewer::set_view called";
	view_ = v;
	emit viewChanged();

	connect(view_, &View::view_changed, this, &PresentationViewer::redraw );


	this->update();
}

void PresentationViewer::switchTool(PresentationViewer::PaintToolType t)
{
	//disconnect the old tool events
    if(currentTool_ != nullptr)
    {
        //disconnect events
        currentTool_->disconnect();
        currentTool_ = nullptr;
    }

	if (tools_.find(t) == tools_.end())
	{
	   return;
	}

	//connect the new tool
    currentTool_ = tools_[t].get();
	connect(this, SIGNAL(mouseMove(QMouseEvent*, QPainter&)), currentTool_, SLOT(mouseMoveEvent(QMouseEvent *, QPainter&)));
	connect(this, SIGNAL(mousePress(QMouseEvent*, QPainter&)), currentTool_, SLOT(mousePressEvent(QMouseEvent *, QPainter&)));
	connect(this, SIGNAL(mouseRelease(QMouseEvent*, QPainter&)), currentTool_, SLOT(mouseReleaseEvent(QMouseEvent *, QPainter&)));


	qDebug() << "PresentationViewer::switchTool called";
}

void PresentationViewer::redraw()
{
	this->update();
}


void PresentationViewer::paint(QPainter* painter)
{
	//paint only when view is active
	if( view_ != nullptr)
	{
		//draw the view content
		painter->save();
		view_->draw_to(contentsBoundingRect(), *painter);
		painter->restore();

		//draw the current overlay of the view when available
		if(view_->hasOverlay())
		{
			//contentsBoundingRect() == painter.viewport().size() ????
			//this upsizes image?
			QSize s = QSize(contentsBoundingRect().size().width(), contentsBoundingRect().size().height());
			QRect area = calcDrawArea(view_->get_overlay()->size(), s);
			painter->drawImage(area, *view_->get_overlay());
		}
	}

	//draw overlay here?
}
