function arrayBufferToBase64( buffer ) 
{
	if(!(buffer && buffer instanceof ArrayBuffer && buffer.byteLength !== undefined)) {
		throw "not an array buffer";
	}
	
    var binary = '';
    var bytes = new Uint8Array( buffer );
    var len = bytes.byteLength;
    for (var i = 0; i < len; i++) {
        binary += String.fromCharCode( bytes[ i ] );
    }
    return window.btoa( binary );
}

function arrayBufferToHex(buffer)
{
	if(!(buffer && buffer instanceof ArrayBuffer && buffer.byteLength !== undefined)) {
		throw "not an array buffer";
	}
	
	var hexstr='';
	var bytes = new Uint8Array( buffer );
    for (var i = 0; i < bytes.byteLength; i++) 
    {
		hexstr += ("00" + bytes[i].toString(16)).slice(-2)
    }
	return hexstr;
}

function str2arraybuffer(str) 
{
	if(typeof str !== 'string')
		throw "wrong type: " + typeof hexstr;
		
	var buf = new ArrayBuffer(str.length*2); // 2 bytes for each char
	var bufView = new Uint16Array(buf);
	for (var i=0, strLen=str.length; i<strLen; i++) {
		bufView[i] = str.charCodeAt(i);
	}
	return buf;
}

function hexstr2arraybuffer(hexstr)
{
	if(typeof hexstr !== 'string')
		throw "wrong type: " + typeof hexstr;
	
	if(hexstr.length % 2 != 0){
		throw "hexstr length should be multiple of 2 length: " + hexstr.length;
	}
	
	var arraybuffer = new ArrayBuffer(hexstr.length/2);
	var dataview = new DataView(arraybuffer);
	
	for(var i = 0; i < hexstr.length;  i+=2)
	{
		var offset = i == 0 ? i : i/2;
		var value = hexstr.substring(i, i+2);
		dataview.setUint8(offset, parseInt(value ,16));
	}
	return arraybuffer;
}


