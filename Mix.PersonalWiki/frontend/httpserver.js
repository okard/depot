#!/usr/bin/env node

var http = require("http"),
	url = require("url"),
	path = require("path"),
	fs = require("fs"),
	port = process.argv[2] || 8888;
	
	
	
function mime_lookup(filename)
{
	switch(path.extname(filename))
	{
		case '.html': 
		case '.htm':
			return 'text/html';
		
		case '.css': return 'text/css';
		case '.js': return 'application/javascript';
		case '.png': return 'image/png';
		
		default: return 'application/octet-stream';
	}
}
 
http.createServer(function(request, response) 
{
	var cwd = process.cwd();
	var uri = url.parse(request.url).pathname;
	var filename = path.join(cwd, uri);
	
	filename = path.resolve(filename);
	
	if(filename.slice(0, cwd.length) != cwd)
	{
		response.writeHead(404, {"Content-Type": "text/plain"});
		response.write("404 Not Found\n");
		response.end();
		return;
	}
	
	fs.exists(filename, function(exists) 
	{
		if(!exists) 
		{
			response.writeHead(404, {"Content-Type": "text/plain"});
			response.write("404 Not Found\n");
			response.end();
			return;
		}
		 
		//look for more files
		if (fs.statSync(filename).isDirectory()) 
			filename += '/index.htm';
		
		//exists
		if(!fs.existsSync(filename))
		{
			response.writeHead(404, {"Content-Type": "text/plain"});
			response.write("404 Not Found\n");
			response.end();
			return;
		}
		 
		fs.readFile(filename, "binary", function(err, file) 
		{
			if(err) 
			{
				response.writeHead(500, {"Content-Type": "text/plain"});
				response.write(err + "\n");
				response.end();
				return;
			}
			 
			response.writeHead(200, {"Content-Type": mime_lookup(filename)});
			response.write(file, "binary");
			response.end();
		});
	});
}).listen(parseInt(port, 10));
 
console.log("Static file server running at\n => http://localhost:" + port + "/\nCTRL + C to shutdown");
