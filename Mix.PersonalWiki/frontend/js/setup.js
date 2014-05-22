


var frontend = 
{
	
	show_page: function(page_key)
	{
		var p = wiki.openPage(page_key);
		
		//page_show
	},
	
	page_set_content: function()
	{
		//page_edit textarea content
	}
	
	
	
};


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

	modeSwitch('show');
	
	$( window ).unload(function() {
		alert( "Bye now!" );
	});
	
});

