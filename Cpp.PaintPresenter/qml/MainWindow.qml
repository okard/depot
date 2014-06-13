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

    //properties for tool management
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
            presentationWindow.showMaximized();
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
            presentationViewer.switchTool(PresentationViewer.Pen)
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
                tooltip: "Choose tool"
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
                tooltip: "Choose tool color"
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
                currentIndex: -1
                textRole: "display"
                onCurrentIndexChanged: {
                    console.log("cmbViews index changed " + currentIndex)
                    view_index = currentIndex
                }
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



    //View handling:
    ViewListModel
    {
        id: views

        onDataChanged: {
            if(count == 1)
            {
                cmbViews.currentIndex = -1;
                cmbViews.model = views;
                cmbViews.currentIndex = 0;
            }

            console.log("views.count: " + count)
        }

    }

    property int view_index
    property View view_current: views.count > 0
                                    && view_index >= 0
                                    && view_index < views.count
                                ? views.get(view_index) : null

    //the presentation viewer (show views)
    PresentationViewer
    {
        id: presentationViewer
        width: parent.width
        height: parent.height

        view: view_current

        /*viewChanged: {
            //update view info label here
            //add a action toolbar? from view.xxxxx
        }*/
    }

    //timer widget dogs
    TimerWidget {
    }

    //presentation window for the second screen
    PresentationWindow
    {
        id: presentationWindow
    }

    onView_indexChanged: {
        console.log("view_index: " + view_index)
    }

    onView_currentChanged: {
        console.log("view_current: " + view_current)
    }
}

