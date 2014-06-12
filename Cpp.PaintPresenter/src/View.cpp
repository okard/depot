
#include "View.hpp"



const QString& View::name() const
{
	return this->name_;
}

QImage& View::get_overlay()
{

}

void View::draw_to(const QRect& dirtyRect, QPainter& painter)
{

}
