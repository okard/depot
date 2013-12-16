import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0


import "MainWindow.js" as Logic

ApplicationWindow {
	id: mainWindow
	color: "#FFFFFF"
	width: 800; height: 800
	visible: true


	toolBar: ToolBar
	{
		RowLayout
		{
			ToolButton
			{
			   iconSource: "../images/icon_pen2.png"
			   text: "Pen"
			}

			ToolButton
			{
			   iconSource: "../images/icon_pdf.png"
			   text: "Open PDF File"
			   onClicked: Logic.openPdfFile()
			}

			ComboBox
			{
				id: cmbViews
			}
		}
	}

	FileDialog
	{
		id: fileDialog
		title: "Please choose a file"
		nameFilters: [ "PDF Files (*.pdf)" ]

	}


	PresenterWidget
	{
		width: parent.width
		height: parent.height
	}

}
