#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QColor>

enum class PaintTool
{
    Pen,
    Rectangle,
    Highlight,
    Text,
    Erease
};


class PaintWidget : public QWidget
{
    Q_OBJECT

private:
    //core paint stuff
    QImage image_;
    QPainter painter_;


    bool isPainting_;


    bool drawScreenhot_;
    QPixmap screenhot_;

    //pdf support
    //paint settings
    //current paint mode? pen/rect/etc
    PaintTool paintTool_;

    QColor penColor_;
    int penWidth_;
    QPoint penLastPoint_;

    QRect rectTool;


public:
    explicit PaintWidget(QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void drawLineTo(const QPoint &endPoint);

signals:
    
public slots:
    //pen color slot?
    void makeScreenshot();
    void clearScreenshot();
    void clearDrawings();

    void setPenColor(const QColor& color);
    void setPenWidth(int penWidth);

    void setTool(PaintTool tool);

    //change drawing mode?

    //save
    //clearAll();
    //set width
};

#endif // PAINTWIDGET_H
