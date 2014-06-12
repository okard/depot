#ifndef VIEW_HPP
#define VIEW_HPP

#include <memory>

#include <QImage>


//interface?
class View : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QString name READ name NOTIFY name_changed)
	Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY size_changed)

protected:
    QString name_;
	QSize size_;

public:
	explicit View();

	const QSize& size() const;
	void setSize(const QSize& size);

	const QString& name() const;
    //events

	//get the current overlay
	virtual QImage* get_overlay();

	//has a overlay at the moment
	virtual bool hasOverlay();
	//create a current overlay
	virtual bool createOverlay();

	//virtual void deleteOverlay();

	//clear overlay via presenter viewer

	//draw the current view to painter
	virtual void draw_to(const QRectF& dirtyRect, QPainter& painter);

	//resize stuff -> internal size of view & overlay

	//QString viewInfo();

signals:
	void name_changed();
	void size_changed();

	void view_changed(); //overlay, pdf page
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

	//current view has overlay

signals:
	void page_index_changed(int index);

};


//Image View
	//shows a image + overlay


//Draw View
	//show a whitebackground for drawings

/*

//Screenshot View
class ScreenshotView : public View
{
private:
    //QPixmap

public:

	//static ScreenhotView* create_screenshot();

};
*/


#endif // VIEW_HPP
