

function openPdfFile()
{
    diaOpenPdf.open();


}



function addPdfView(url)
{
    //create pdf view
    var newObject = Qt.createQmlObject('import QtQuick 2.1; import PP 1.0; PdfView { }',
                                        mainWindow, "createPdfView");

    //load the pdf
    newObject.loadPdf(url);

    console.log(newObject.name);

    //append to view listmodel
    views.append(newObject);
}
