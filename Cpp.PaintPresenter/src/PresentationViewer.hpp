#ifndef PRESENTATIONVIEWER_HPP
#define PRESENTATIONVIEWER_HPP

#include <unordered_map>
#include <memory>

#include <QPen>
#include <QPainter>
#include <QQuickPaintedItem>

#include "PaintTool.hpp"
#include "View.hpp"

/**
 * @brief The PresentationViewer class
 *
 * Main QML Widget to show views
 *
 */
class PresentationViewer : public QQuickPaintedItem
{
    Q_OBJECT

	Q_PROPERTY(View* view READ get_view WRITE set_view NOTIFY viewChanged)

public:
    //tools
    enum PaintToolType : unsigned int
    {
        None = 0,
        Pen = 1,
        Rectangle = 2,
        Highlight = 3,
        Text = 4,
        Erease = 5
    };
    Q_ENUMS(PaintToolType)

private:
	//Tool Management:

    QPen pen_;
    std::unordered_map<PaintToolType, std::unique_ptr<PaintTool>, std::hash<unsigned int>> tools_;
    PaintTool* currentTool_ = nullptr;

	//Current view to show
	View* view_;

	//Helper for drawing in OverlayImage
	QPainter overlayPainter_;

public:
    explicit PresentationViewer(QQuickItem *parent = 0);

	//get mouse events
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


	//attach ListModel View property?

	View* get_view();
	void set_view(View* v);

signals:
	void toolChanged();
	void viewChanged();

public slots:
    void switchTool(PaintToolType t);


signals:

	//paint tool mouse events:
	void mouseMove(QMouseEvent* event, QPainter& painter);
	void mousePress(QMouseEvent* event, QPainter& painter);
	void mouseRelease(QMouseEvent* event, QPainter& painter);

// QQuickPaintedItem interface
public:
   void paint(QPainter* painter);
};

#endif // PRESENTATIONVIEWER_HPP
