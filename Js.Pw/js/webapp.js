
/**
* create a array buffer result from master password salt and the given url
*/
function run_algorithm(algorithm, mpw_salt, url)
{
	if(!mpw_salt || typeof mpw_salt !== 'string' || mpw_salt.length <= 0 ) {
		throw "mpw_salt should be a string with content";
	}
	
	if(!url && typeof url !== 'string' ) {
		throw "url should be a string";
	}
	
	switch(algorithm)
	{
		case 'PBKDF2':
			var hexstr = CryptoJS.PBKDF2(url, mpw_salt, { keySize: 512/32, iterations: 1000 }).toString();
			return hexstr2arraybuffer(hexstr);
			
		case 'BLAKE2S':
			var key = new Uint8Array(str2arraybuffer(mpw_salt));
			var url = new Uint8Array(str2arraybuffer(url));
			var blake = new BLAKE2s(32, key);
			blake.update(url);
			var result = blake.digest();
			return result.buffer; 
		default: throw "invalid algorithm";
	}
}

/**
* Convert a array buffer result into choosen string encoding
*/
function encode_result(encoding, result)
{
	//todo require byte array?
	if(!(result && result instanceof ArrayBuffer && result.byteLength !== undefined)) {
		throw "not an array buffer";
	}
	
	switch(encoding)
	{
		case 'hex':
			return arrayBufferToHex(result);
		case 'base64': 
			return arrayBufferToBase64(result);
		case 'base64url': 
			var base64 = arrayBufferToBase64(result);
			return base64.replace(/\+/g, "-").replace(/\//g, "_");
		case 'base91':
			return base91.encode(new Uint8Array(result));
		default: throw "invalid encoding method";
	}
}

/**
* Creates the password key string
*/
function create_pw()
{
	//collect values
	var mpw_salt = document.getElementById('txtMasterPw').value; //master password salt
	var url = document.getElementById('txtUrl').value;
	var algorithm = document.getElementById('lstAlgorithm').value;
	var encoding = document.getElementById('lstEncoding').value;
	var numLimitLength = document.getElementById('numLength').value;
	var txtResult = document.getElementById('txtResult');
	txtResult.value ='';
	
	document.body.style.cursor = 'wait';
	
	//create result, encoding string, and cut string
	var base_result = run_algorithm(algorithm, mpw_salt, url);
	var encoded_result = encode_result(encoding, base_result);
	var final_result = encoded_result;
	
	document.getElementById('lblWarning').textContent ='';
	
	//limit to length if only a specific length is allowed (reduce safety!!!!)
	if(numLimitLength && numLimitLength > 0)
	{
		final_result = final_result.substring(0, numLimitLength);
		document.getElementById('lblWarning').textContent ='Reduced safety by limiting length of key';
	}
	
	//show results
	txtResult.value = final_result;
	txtResult.focus();
	txtResult.select();
	
	document.getElementById('lblKeyInfo').textContent = 'KeyInfo: Key-Bytes=' + base_result.byteLength
			+ '; Result-Length=' + encoded_result.length 
			+ '; Final-Length=' + final_result.length;
	
	document.body.style.cursor = 'auto';
}
