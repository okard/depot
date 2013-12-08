import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
	id: mainWindow
	color: "#FFFFFF"
	width: 800; height: 800


	toolBar: ToolBar
	{
		RowLayout
		{
			ToolButton
			{
			   iconSource: "../images/icon_pen2.png"
			   text: "Pen"
			}

			ComboBox
			{
			}
		}
	}

}
