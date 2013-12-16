

function openPdfFile()
{
	var dialog = Qt.createComponent("FileDialog");
	dialog.open();
	//fileDialog.open();
	//fileDialog.accepted.connect(function(){console.log("test")});
}
