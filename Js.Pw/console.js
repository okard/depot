#!/usr/bin/env node


var vm = require("vm");
var fs = require("fs");

var data = fs.readFileSync('pbkdf2.js');
vm.runInNewContext(data, this, 'pbkdf2.js');

var PBKDF2 = this.CryptoJS.PBKDF2;

var readline = require('readline');
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.question("Masterpassword? ", function(pw) {
	rl.question("Url? ", function(url) {
		console.log("Key:", PBKDF2(url, pw, { keySize: 512/32, iterations: 1000 }).toString());
		rl.close();
	});
});



