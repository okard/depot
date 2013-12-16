#ifndef PAINTTOOL_HPP
#define PAINTTOOL_HPP

#include <QObject>

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

    const QPen& pen_;
public:

    explicit PaintTool(const QPen& pen);
    virtual ~PaintTool();


    //events

public slots:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

    //disable
    //enable

    //temp drawings
};


//Pen
class PenTool : public PaintTool
{
    Q_OBJECT

public:
    explicit PenTool(const QPen& pen);
    virtual ~PenTool();


public slots:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
};




#endif // PAINTTOOL_HPP
