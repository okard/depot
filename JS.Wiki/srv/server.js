


exports.Server = function(config)
{

    
    
    this.handler = function (req, res)
    {
        res.writeHead(200, {'Content-Type': 'text/plain'});
        res.end('Wiki Backend\n');
    }
}

