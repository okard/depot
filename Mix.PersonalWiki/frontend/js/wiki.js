
/*
 Interface to the application REST interface
 
 no html references here take it from frontend
 TODO jquery objects or functions
*/

/**
* represents a wiki page
*/
function Page()
{
	var obj = 
	{
		content: undefined,
		type: "markdown",
		id: undefined,
		
		//meta
		//name
		
		//attachments
		
		//raw_data
		//rendered_data	
		
		
		//save?
	};
	
	return obj;
}

/**
* main wiki object
*/

function Wiki() 
{
	var obj =
	{
		content_container: undefined,
		//service_url 
		
		//current page
		
		//mode: Show, Edit, History, Attachments, Subpages, Metadata

		//load page
		openPage: function(page)
		{
			alert('open page: ' + page);
			//load a page and return it?
			
			return new Page();
		},
		
		page_to_string: function(page)
		{
			return JSON.stringify(page);
		}
		
		//get categories
		
		//render function? (markdown)
		
		//backend
	};
	
	
	return obj;
}
