#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QColor>


namespace Poppler { class Document; }

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
    QSize outputSize_;
    QImage image_; //overlay image
    QPainter painter_;

    //screenshot
    bool drawScreenhot_;
    QPixmap screenshot_;

    //pdf
    bool drawPdf_;
    Poppler::Document* pdfDocument_;
    unsigned int pdfCurrentPage_;
    QImage pdfImage_;


    //paint settings
    PaintTool paintTool_;   //current paint tool
    bool isPainting_;       //is currently painting

    //pen stuff
    //QPen
    QColor penColor_;
    int penWidth_;
    QPoint penLastPoint_;

    //rectangle stuff
    QRect rectTool;

    //erease stuff


public:
    explicit PaintWidget(QWidget *parent = 0);
    virtual ~PaintWidget();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void drawLineTo(const QPoint &endPoint);

signals:
    //paint update event (for presentation window)
    
public slots:
    //resize

    //pen color slot?
    void makeScreenshot();
    void clearScreenshot();
    void clearDrawOverlay();

    void setPenColor(const QColor& color);
    void setPenWidth(int penWidth);

    void setTool(PaintTool tool);


    void openPdfFile(const QString& filename);
    void closePdfFile();
    //change drawing mode?

    void nextPdfPage();
    void prevPdfPage();

    //set output size
    //save
    //clearAll();
    //set width
private:
    void makePdfImage();
};

#endif // PAINTWIDGET_H
