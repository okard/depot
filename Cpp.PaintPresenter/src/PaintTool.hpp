#ifndef PAINTTOOL_HPP
#define PAINTTOOL_HPP

#include <QObject>

#include <QPoint>
#include <QPainter>


class QMouseEvent;


//Pen,
//Rectangle,
//Highlight,
//Text,
//Erease

/**
 * @brief The Tool class
 * Basic Class for Drawings/Paint Tools
 */
class PaintTool : public QObject
{
    Q_OBJECT
private:
    //state active
    //temp data

    //QPixmap& overlay_;

    //access to overlay/painter
protected:
    const QPen& pen_;
public:

    explicit PaintTool(const QPen& pen);
    virtual ~PaintTool();

	//access to QImage, QPainter???
	//best way?
	//add to events?
    //events

	//temp draw

public slots:
	//mouseMoveEvent(QMouseEvent* QPainter*);
	virtual void mouseMoveEvent(QMouseEvent* event, QPainter& p);
	virtual void mousePressEvent(QMouseEvent* event, QPainter& p);
	virtual void mouseReleaseEvent(QMouseEvent* event, QPainter& p);

    //disable
    //enable

    //temp drawings
};


//Pen
class PenTool : public PaintTool
{
    Q_OBJECT

private:
	QPoint penLastPoint_;

public:
    explicit PenTool(const QPen& pen);
    virtual ~PenTool();



public slots:
	//mouseMoveEvent(QMouseEvent* QPainter*);
	virtual void mouseMoveEvent(QMouseEvent* event, QPainter& p);
	virtual void mousePressEvent(QMouseEvent* event, QPainter& p);
	virtual void mouseReleaseEvent(QMouseEvent* event, QPainter& p);

private:
	void drawLineTo(QPainter& p, const QPoint &endPoint);

};




#endif // PAINTTOOL_HPP
