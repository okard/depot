


function modeSwitch(mode)
{
	//alert('mode switch: ' + mode);
	
	var container = $('#page');
	container.children('div').hide();
	container.children('#page_'+mode).show();
}




$(document).ready(function() 
{
	var wiki = new Wiki();
	window.wiki = wiki;
	
	wiki.content_container = $('#page');
	
	
	//get categories and add them to menu
	
	//templates for 
		//Show
		//Edit
		//History
		//Attachments
		//Subpages
		//Metadata

	modeSwitch('show');
	
	
	$( window ).unload(function() {
		alert( "Bye now!" );
	});
	
});

