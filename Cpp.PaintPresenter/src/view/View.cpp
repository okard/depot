
#include "View.hpp"


View::View()
	: size_(1024, 768)
{

}

const QSize& View::size() const
{
	return size_;
}

void View::setSize(const QSize& size)
{
	size_ = size;
	emit size_changed();
}

const QString& View::name() const
{
	return name_;
}

QImage* View::get_overlay()
{
	return nullptr;
}

bool View::hasOverlay()
{
	return false;
}

bool View::createOverlay()
{
	return false;
}

void View::draw_to(const QRectF&, QPainter&)
{

}

bool View::doCommand(const QString&)
{
	return false;
}
