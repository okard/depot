/*
 JavaScript Utility Library
 Licensed under GPLv3
 Author: okard
*/

/**
* Load javascript files
*/
function include(url)
{
    if(!(jQuery))
    {
        alert("jQuery library is required to use import function");
        return;
    }
    
    $.ajax({
    url: url,
    dataType: 'script',
    async: true,
    error: function(jqXHR, textStatus, errorThrown){ alert("Error loading: " + url + " " + textStatus + " " + errorThrown);}
    });
}
