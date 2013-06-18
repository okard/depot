#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QColor>

class PaintWidget : public QWidget
{
    Q_OBJECT

private:
    //core paint stuff
    QImage image_;
    QPainter painter_;
    bool isPainting_;
    QPoint lastPoint_;

    QPixmap screenhot_;

    //pdf support
    //paint settings
    //current paint mode? pen/rect/etc

    QColor penColor_;
    int penWidth_;

    bool drawScreenhot_;

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

    //change drawing mode?

    //save
    //clearAll();
    //set width
};

#endif // PAINTWIDGET_H
