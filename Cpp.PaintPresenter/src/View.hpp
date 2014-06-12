#ifndef VIEW_HPP
#define VIEW_HPP

#include <QMap>
#include <QImage>


//forward declaration
namespace Poppler { class Document; }


//interface?
class View : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString name_ READ name)

private:
    QString name_;


public:
    //events

	//get the current overlay
	virtual QImage& get_overlay() = 0;

	//draw the current view to painter
	virtual void draw_to(const QRect& dirtyRect, QPainter& painter) = 0;

	//resize stuff -> internal size of view & overlay

    //name
	QString& name();
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



//Pdf View
class PdfView : public PageableView
{
private:
	//PDF Handling:
    Poppler::Document* pdfDocument_;    //the pdfDocument (use std::unique_ptr)
    unsigned int pdfCurrentPage_;       //current page
	QImage pdfImage_;                   //the current pdf page as image

	//Overlay Handling:
    QMap<unsigned int, QImage> overlays_; //overlay for each page

public:

	//create from file
	//static PdfView* open_file();
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
