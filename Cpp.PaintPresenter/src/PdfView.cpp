#include "PdfView.hpp"

#include <QDebug>
#include <QPainter>

#include <poppler/qt5/poppler-qt5.h>

#include "Helper.hpp"


PdfView::PdfView()
	: pdfCurrentPage_(0)
{

	//connect to resize event of view
}

PdfView::~PdfView()
{

}

void PdfView::loadPdf(QUrl file)
{
	this->pdfDocument_.reset(Poppler::Document::load(file.path()));

	if (!this->pdfDocument_)
	{
		qDebug() << "cant load: " << file;
		//todo error signal
		return;
	}

	this->name_ = file.fileName();

	pdfDocument_ ->setRenderHint(Poppler::Document::TextAntialiasing, true);
	pdfDocument_ ->setRenderHint(Poppler::Document::Antialiasing, true);
	pdfDocument_->setRenderBackend(Poppler::Document::SplashBackend);

	updatePdfImage();
}

QImage* PdfView::get_overlay()
{
	if(hasOverlay())
		return &overlays_[page_index()];
	//look if current page has a overlay

	return nullptr;
}

bool PdfView::hasOverlay()
{
	return overlays_.contains(page_index());
}


void PdfView::draw_to(const QRectF&, QPainter& painter)
{
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setRenderHint(QPainter::Antialiasing, true);
	//painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

	//draw pdf if available
	if(pdfDocument_)
	{
	   //QSize s(4, 3);
	   QRect area = calcDrawArea(pdfImage_.size(), painter.viewport().size());
	   //std::cout << area.x() << ' ' << area.y() << ' ' << area.width() << ' ' << area.height() << std::endl;
	   painter.drawImage(area, pdfImage_);
	}
}

void PdfView::updatePdfImage()
{
	if(!pdfDocument_)
		return;

	//TODO calculate right dpi for output size
	std::unique_ptr<Poppler::Page> page(pdfDocument_->page(pdfCurrentPage_));

	auto page_size = page->pageSize(); //page size in points, 72 dpi == each point one pixel
	auto rect = calcDrawArea(page_size, this->size()); //scale up to view size

	//extract factor
	float xfactor = 72.0 * ((qreal)rect.width()/(qreal)page_size.width());
	float yfactor = 72.0 * ((qreal)rect.height()/(qreal)page_size.height());
	pdfImage_ = page->renderToImage(xfactor, yfactor);

	qDebug() << "PDF_Image size: " << pdfImage_.width() << ", " << pdfImage_.height();

	emit view_changed();
}


int PdfView::page_index()
{
	return pdfCurrentPage_;
}

void PdfView::page_next()
{
	if(pdfDocument_ == nullptr)
		return;

	pdfCurrentPage_ = clamp<int>(pdfCurrentPage_ + 1, 0, pdfDocument_->numPages()-1);
	updatePdfImage();
}

void PdfView::page_prev()
{
	if(pdfDocument_ == nullptr)
		return;

	pdfCurrentPage_ = clamp<int>(pdfCurrentPage_ - 1, 0, pdfDocument_->numPages()-1);
	updatePdfImage();
}

void PdfView::page_set(int index)
{
	if(pdfDocument_ == nullptr)
		return;

	pdfCurrentPage_ = clamp<int>(index, 0, pdfDocument_->numPages()-1);
	updatePdfImage();
}

bool PdfView::createOverlay()
{
	if(!hasOverlay())
	{
		//overlay in the same size as the corospending pdf page
		overlays_[page_index()] = QImage(pdfImage_.size(), QImage::Format_ARGB32);
		//overlays_[page_index()].fill(QColor::fromRgb(255,0,0,30));
		overlays_[page_index()].fill(QColor::fromRgb(0,0,0,0));
		emit view_changed();

		qDebug() << "Overlay_Image size: " << overlays_[page_index()].width()
								   << ", " << overlays_[page_index()].height();
		return true;
	}
	return false;
}
