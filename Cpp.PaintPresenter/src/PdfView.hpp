#ifndef PDFVIEW_HPP
#define PDFVIEW_HPP

#include <QUrl>

#include "View.hpp"


namespace Poppler { class Document; }

//Pdf View
class PdfView : public PageableView
{
	Q_OBJECT

private:
	//PDF Handling:
	std::unique_ptr<Poppler::Document> pdfDocument_;    //the pdfDocument (use std::unique_ptr)
	unsigned int pdfCurrentPage_;       //current page
	QImage pdfImage_;                   //the current pdf page as image

	//Overlay Handling:
	QMap<unsigned int, QImage> overlays_; //overlay for each page

public:
	 explicit PdfView();
	~PdfView();

	//access for preview and co?
		//show next and prev page

	//create from file
	//static PdfView* open_file();

	// View interface

public slots:
	void loadPdf(QUrl file);

public:

	QImage& get_overlay();
	void draw_to(const QRect& dirtyRect, QPainter& painter);

	// PageableView interface
public:
	int page_index();
	void page_next();
	void page_prev();
	void page_set(int index);
};


#endif // PDFVIEW_HPP
