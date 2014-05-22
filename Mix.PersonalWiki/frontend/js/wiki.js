

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
