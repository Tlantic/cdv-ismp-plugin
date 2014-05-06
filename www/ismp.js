 /* global module, require */
'use strict';

var exec = require('cordova/exec');

// secure copy definition
function iSMP(){
    this.pluginRef = 'iSMP';                              // *** Plugin reference for Cordova.exec calls
}

// connect-load method
iSMP.prototype.load = function (successCallback, errorCallback) {
	exec(successCallback, errorCallback, this.pluginRef, 'loadTerminal', []);
};

// return connection status
iSMP.prototype.isConnected =  function (successCallback, errorCallback) {
               exec(successCallback, errorCallback, this.pluginRef, 'isTerminalConnected', []);
};
               
// return terminal status
iSMP.prototype.getStatus =  function (successCallback, errorCallback) {
               exec(successCallback, errorCallback, this.pluginRef, 'getTerminalStatus', []);
};
module.exports = new iSMP();