#ifndef HELPER_HPP
#define HELPER_HPP

#include <QRect>


//scales source up to fit in target size
	// for example QSize(4,3) as in this format to target area
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

static QPointF translatePoint(QPointF original, QRect source, QRectF target)
{
	double x = original.x();
	double y = original.y();

	// calculate scale:
	double x_scale = target.width() / source.width();
	double y_scale = target.height() / source.height();

	return QPointF(x * x_scale, y * y_scale);
}




#endif // HELPER_HPP
