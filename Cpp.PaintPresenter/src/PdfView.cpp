#include "PdfView.hpp"

#include <QDebug>

#include <poppler/qt5/poppler-qt5.h>


PdfView::PdfView()
{

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
}

QImage& PdfView::get_overlay()
{
}

void PdfView::draw_to(const QRect& dirtyRect, QPainter& painter)
{
}

int PdfView::page_index()
{
}

void PdfView::page_next()
{
}

void PdfView::page_prev()
{
}

void PdfView::page_set(int index)
{
	//page signal
}
