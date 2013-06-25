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

//16:9, 4:3 enum?


class PaintWidget : public QWidget
{
    Q_OBJECT

private:
    //core paint stuff
    QSize outputSize_;

    QPainter overlayPainter_;
    QImage overlayImage_; //overlay image //save for pdf pages

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
    //QPen pen_;
    QColor penColor_;
    int penWidth_;
    QPoint penLastPoint_;

    //rectangle stuff
    QRect rectTool;

    //erease stuff

    bool autoOutputSize_ = true;


public:
    explicit PaintWidget(QWidget *parent = 0);
    virtual ~PaintWidget();


    //void drawTo(QPainter& painter);


    bool& autoOutputSize() { return autoOutputSize_; }

    //properties: current page, paintool, etc
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void drawLineTo(const QPoint &endPoint);

signals:
    //paint update event (for presentation window) (dirtyrect?)
    
public slots:
    //resize
    //set output size
    void updateOutputSize(const QSize& size);

    //overlay tools
    void setTool(PaintTool tool);
    void setPenColor(const QColor& color);
    void setPenWidth(int penWidth);
    void clearDrawOverlay();

    //screenshot tools
    void makeScreenshot();
    void clearScreenshot();

    //pdf tools
    void openPdfFile(const QString& filename);
    void closePdfFile();
    void nextPdfPage();
    void prevPdfPage();
    //hide pdf?

    //saveOverlayImage(filename)
    //clearAll();
    //set width
private:
    void updatePdfPageImage();
};

#endif // PAINTWIDGET_H
