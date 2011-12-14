/**
* Niki
* License: GPLv3
* Author: okard
*/

var niki =
{
    status: 'notconnect',
    server: 'http://127.0.0.1:8080',
    
    /**
    * Load a page from vfs
    */
    load: function(name)
    {
        //load wikipage
        alert('load page');
        
        var req = 
        {
            cmd: "list"
        };
        
        this.dbRequest(req, function(data)
        {
            alert(data);
        });
    },

    /**
    * make a db request
    */
    dbRequest: function(req, callback)
    {
         $.ajax({
          type: 'POST',
          url: this.server+"/$db",
          data: JSON.stringify(req),
          success: function(data, textStatus, jqXHR)
          {
            callback(data);
          }
        });
    },

}