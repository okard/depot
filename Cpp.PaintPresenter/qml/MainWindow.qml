import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


import PP 1.0

import "MainWindow.js" as Logic

ApplicationWindow {
	id: mainWindow
	color: "#FFFFFF"
	width: 800; height: 800
	visible: true

    property color tool_color: "black"
    property url tool_icon_source

    Action {
            id: actionOpenPdf
            text: "&Open Pdf"
            shortcut: "Ctrl+O"
            onTriggered: Logic.openPdfFile()
            tooltip: "Open an image"
            iconSource: "../images/icon_pdf.png"
    }

    Action {
        id: actionMakeScreenshot
        text: "&Make Screenshot"
        shortcut: "Ctrl+#"
        //onTriggered: Logic.openPdfFile()
        tooltip: "Creates a screenshot view"
        iconSource: "../images/monitor-8x.png"
    }

    Action {
        id: actionCloseView
        text: "&Close view"
        shortcut: "Ctrl+C"
        //onTriggered: Logic.openPdfFile()
        tooltip: "Close view"
        iconSource: "../images/circle-x-8x.png"
    }

    Action {
        id: actionShowPresentation
        text: "show presentation"

        onTriggered: {
            presentationWindow.show();
        }
    }

    //page_next
    //page_prev

    //view remove
    //view next
    //view prev

    //view first
    //view last


    Action {
        id: actionToolPen
        text: "Pen"
        shortcut: "Ctrl+P"
        iconSource: "../images/icon_pen2.png"
        onTriggered: {
            mainWindow.tool_icon_source = iconSource
        }
    }


    Action {
        id: actionToolMarker
        text: "Pen"
        shortcut: "Ctrl+M"
        iconSource: "../images/icon_highlighter.png"
        onTriggered: {
            mainWindow.tool_icon_source = iconSource
        }
    }


    //the main toolbar
	toolBar: ToolBar
	{
		RowLayout
		{
            //Tool Chooser
            ToolButton
            {

                style: ButtonStyle {
                        label:
                            RowLayout{ Image {
                                source: tool_icon_source
                                sourceSize.width: 20
                                sourceSize.height: 20
                            }}

                }

                menu: Menu
                {
                    title: "Tool Choose"
                    MenuItem { action: actionToolPen }
                    MenuItem { action: actionToolMarker }
                }
            }

            //Color Chooser
            ToolButton {
                onClicked: toolColorDialog.open()
                style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 25
                            implicitHeight: 25
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            color: mainWindow.tool_color

                        }
                    }
                //color dialog for tool color
                ColorDialog {
                    id: toolColorDialog
                    title: "Please choose a color"
                    onAccepted: {
                        mainWindow.tool_color = color
                    }
                }
            }


            ToolButton { action: actionOpenPdf }
            ToolButton { action: actionMakeScreenshot }

            //
            Text {
                text: " View: "
            }

			ComboBox
			{
				id: cmbViews
                width: 200
                model: views
                textRole: "name"
			}

            ToolButton { action: actionCloseView }

            Text {
                text: " View Size: "
            }

            ComboBox
            {
                id: cmbViewSize
                model: [ "MainWindow", "PresentationWindow", "1024x768", "1600x1080" ]
            }


            Text {
                text: "View Info: "
            }


            ToolButton { action: actionShowPresentation }
		}
	}

    //pdf file dialog
	FileDialog
	{
        id: diaOpenPdf
		title: "Please choose a file"
		nameFilters: [ "PDF Files (*.pdf)" ]
        onAccepted: Logic.addPdfView(diaOpenPdf.fileUrl)
	}


    ListModel
    {
        id: views
    }

    property int view_index: cmbViews.currentIndex
    property View view_current: views.count > 0 && view_index > 0 && view_index < views.count
                                ? views[view_index] : null


    //the presentation viewer (show views)
    PresentationViewer
    {
        id: presentationViewer
        width: parent.width
        height: parent.height
    }

    TimerWidget {

    }


    //presentation window for the second screen
    PresentationWindow
    {
        id: presentationWindow
    }

    PdfView {
        id: testView
    }
}

