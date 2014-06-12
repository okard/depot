#ifndef PDFVIEW_HPP
#define PDFVIEW_HPP

#include <QUrl>
#include <QMap>

#include "View.hpp"


namespace Poppler { class Document; }

//Pdf View
class PdfView : public PageableView
{
	Q_OBJECT

private:
	//PDF Handling:
	std::unique_ptr<Poppler::Document> pdfDocument_;    //the pdfDocument (use std::unique_ptr)
	int pdfCurrentPage_;       //current page
	QImage pdfImage_;                   //the current pdf page as image

	//Overlay Handling:
	QMap<unsigned int, QImage> overlays_; //overlay for each page

public:
	 explicit PdfView();
	~PdfView();

	//access for preview and co?
		//show preview of next and prev page

	// View interface

	QImage* get_overlay();
	bool hasOverlay();
	bool createOverlay();
	void draw_to(const QRectF& dirtyRect, QPainter& painter);

public slots:
	void loadPdf(QUrl file);

// PageableView interface
public:
	int page_index();
	void page_next();
	void page_prev();
	void page_set(int index);

private:
	void updatePdfImage();
};


#endif // PDFVIEW_HPP
