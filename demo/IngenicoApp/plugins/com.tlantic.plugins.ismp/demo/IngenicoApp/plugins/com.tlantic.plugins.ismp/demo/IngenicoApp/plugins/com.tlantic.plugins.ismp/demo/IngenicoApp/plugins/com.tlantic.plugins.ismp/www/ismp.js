/* global module, require */
'use strict';

var exec = require('cordova/exec');

// secure copy definition
function iSMP(){
    this.pluginRef = 'iSMP';                              // *** Plugin reference for Cordova.exec calls
}

// connect method
iSMP.prototype.load = function (successCallback, errorCallback) {
	exec(successCallback, errorCallback, this.pluginRef, 'loadTerminal', []);
};

module.exports = new iSMP();