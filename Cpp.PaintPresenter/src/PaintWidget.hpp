#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QColor>

#include "View.hpp"
#include "PaintTool.hpp"


namespace Poppler { class Document; }


enum class PaintToolType
{
    Pen,
    Rectangle,
    Highlight,
    Text,
    Erease
};

enum class Scaling
{
    AcademyRatio, // 4:3
    Widescreen    // 16:9
};


/**
 * @brief The PaintWidget class
 */
class PaintWidget : public QWidget
{
    Q_OBJECT

private:
    //core paint stuff
    QSize outputSize_;  //fixed?


    //list of views

    QPainter overlayPainter_;
    QImage overlayImage_; //overlay image //save for pdf pages

    //std::unordered_map<int, QImage> overlays_;

    //screenshot
    bool drawScreenhot_;    //draw screenshot or not
    QPixmap screenshot_;    //buffer for screenshot

    //pdf
    bool drawPdf_; //draw the pdf
    Poppler::Document* pdfDocument_;    //the pdfDocument (use std::unique_ptr)
    unsigned int pdfCurrentPage_;       //current page
    QImage pdfImage_;                   //the pdf page as image

    //paint settings
    PaintToolType paintTool_;   //current paint tool
    bool isPainting_;       //is currently painting

    //pen stuff
    QPen pen_;
    //QColor penColor_;
    //int penWidth_;

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

    //current view
    //current overlay

    //views list
    //overlays list

    //current tool


    //properties: current page, paintool, has pdf etc

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void drawLineTo(const QPoint &endPoint);

signals:
    // change event for active drawings
    void drawingsChanged(const QRect& dirtyRect);

    //view changed
    //overlay changed

    
public slots:
    //resize
    //set output size
    void updateOutputSize(const QSize& size);

    //overlay tools
    void setTool(PaintToolType tool);
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

    //paint the current view to painter
    void paintTo(const QRect& dirtyRect, QPainter& painter);

    //saveOverlayImage(filename)
    //clearAll();
    //set width
private:
    void updatePdfPageImage();
};

#endif // PAINTWIDGET_H
