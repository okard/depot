

function run_algorithm(algorithm, mpw_salt, url)
{
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
	}
}

function encode_result(encoding, result)
{
	//todo require byte array?
	if(!(result && result instanceof ArrayBuffer && result.byteLength !== undefined))
	{
		console.log("not an array buffer");
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
	}
}

function create_pw()
{
	//collect values
	var mpw_salt = document.getElementById('txtMasterPw').value; //master password salt
	var url = document.getElementById('txtUrl').value;
	var algorithm = document.getElementById('lstAlgorithm').value;
	var encoding = document.getElementById('lstEncoding').value;
	var numLimitLength = document.getElementById('numLength').value;
	
	
	document.body.style.cursor = 'wait';
	
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
	
	document.getElementById('txtResult').value = final_result;
	
	document.getElementById('lblKeyInfo').textContent = 'KeyInfo: ' + base_result.byteLength + ' Base-Length '
			+ encoded_result.length + ' Result-Length '
			+ final_result.length + ' Final-Length';
	
	document.body.style.cursor = 'auto';
}



function doit()
{
	var mpw_salt = document.getElementById('txtMasterPw').value;
	var url = document.getElementById('txtUrl').value;
	
	document.body.style.cursor = 'wait';
	var result = CryptoJS.PBKDF2(url, mpw_salt, { keySize: 512/32, iterations: 1000 });
	document.body.style.cursor = 'auto';
	document.getElementById('txtResult').value = result;
}
