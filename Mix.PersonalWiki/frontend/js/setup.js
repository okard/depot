

/*
Frontend interface handling html stuff?


  $("#div1").load("demo_test.txt",function(responseTxt,statusTxt,xhr){
    if(statusTxt=="success")
      alert("External content loaded successfully!");
    if(statusTxt=="error")
      alert("Error: "+xhr.status+": "+xhr.statusText);
  });

*/
var frontend = 
{
	show_page: function(page_key)
	{
		var p = wiki.openPage(page_key);
		
		//page_show
		frontend.load_tpl("tpl/show_page.html");
	},
	
	page_new: function()
	{
		frontend.load_tpl("tpl/show_page.html");
	},
	
	
	page_set_content: function()
	{
		//page_edit textarea content
	},
	
	show_error: function(error_text)
	{
		alert(error_text);
	},
	
	load_tpl: function(file) //TODO callback on sucess
	{
		$("#contentMain").load(file, function(responseTxt,statusTxt,xhr)
		{
			if(statusTxt=="error")
				frontend.show_error("Error: "+xhr.status+": "+xhr.statusText);
			//if(statusTxt=="success") success callback
		});
	},
	
	load_setting_tpl: function()
	{
		frontend.load_tpl("tpl/settings.html");
	}
};

//hides old element show the new
function modeSwitch(mode)
{
	//alert('mode switch: ' + mode);
	var container = $('#page');	//get container
	container.children('div').hide(); //hide all divs
	container.children('#page_'+mode).show(); //show the right one
}


$(document).ready(function() 
{
	// setup wiki handler
	var wiki = new Wiki();
	window.wiki = wiki;
	wiki.content_container = $('#page'); //todo callback?
	
	
	//setup frontend stuff
	
	//get categories and add them to menu
	frontend.load_tpl("tpl/show_page.html");
	modeSwitch('show');
	
	
	window.onbeforeunload = function() {
		//return non void when something changed is not saved
		return;
		return 'Abc bla bla bla';
	};
	
});

