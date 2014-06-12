#ifndef VIEW_HPP
#define VIEW_HPP

#include <memory>

#include <QMap>
#include <QImage>


//forward declaration
namespace Poppler { class Document; }


//interface?
class View : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QString name READ name NOTIFY name_changed)

protected:
    QString name_;

public:
	const QString& name() const;
    //events

	//get the current overlay
	virtual QImage& get_overlay();

	//draw the current view to painter
	virtual void draw_to(const QRect& dirtyRect, QPainter& painter);

	//resize stuff -> internal size of view & overlay

signals:
	void name_changed();
};



/**
 * @brief The PageableView class
 * A pageable view like for pdf files
 */
class PageableView : public View
{
	Q_OBJECT

public:
	//page_change slot

	virtual int page_index() = 0;
	virtual void page_next() = 0;
	virtual void page_prev() = 0;
	virtual void page_set(int index) = 0;


signals:
	void page_index_changed(int index);

};


//Image View
	//shows a image + overlay


//Draw View
	//show a whitebackground for drawings


//Screenshot View
class ScreenshotView : public View
{
private:
    //QPixmap

public:

	//static ScreenhotView* create_screenshot();

};


#endif // VIEW_HPP
