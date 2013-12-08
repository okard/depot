#ifndef VIEW_HPP
#define VIEW_HPP

#include <QMap>
#include <QImage>


//forward declaration
namespace Poppler { class Document; }



//Type of views
enum class ViewType
{
    None,
    Pdf,
    Screenshot
};


//interface?
class View
{
private:
    ViewType type_;
public:

    //events

    //overlay

    //name

};


//Pdf View
class PdfView : public View
{
private:
    Poppler::Document* pdfDocument_;    //the pdfDocument (use std::unique_ptr)
    unsigned int pdfCurrentPage_;       //current page
    QImage pdfImage_;                   //the pdf page as image

    QMap<unsigned int, QImage> overlays_; //overlay for each page
public:


};


//Screenshot View
class ScreenshotView : public View
{
private:
    //QPixmap

public:

};


#endif // VIEW_HPP
