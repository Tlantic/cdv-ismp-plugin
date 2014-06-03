cordova.define("com.tlantic.plugins.ismp.iSMP", function(require, exports, module) {  /* global module, require */
'use strict';

var exec = require('cordova/exec');

// secure copy definition
function iSMP() {
	this.pluginRef = 'iSMP';                              // *** Plugin reference for Cordova.exec calls ***/
	this.connectionEvent = 'iSMP_CON_STATUS_CHANGE';
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
               
// puchase operation
iSMP.prototype.purchase = function (receiptCode, amount, successCallback, errorCallback) {
	exec(successCallback, errorCallback, this.pluginRef, 'doPurchase', [receiptCode, amount]);
};

// refund operation
iSMP.prototype.refund = function (posId, receiptCode, amount, originalDate, originalTime, successCallback, errorCallback) {
    exec(successCallback, errorCallback, this.pluginRef, 'doRefund', [posId, receiptCode, amount, originalDate, originalTime]);
};

// open accounting period
iSMP.prototype.openAP = function (receiptCode, successCallback, errorCallback) {
    exec(successCallback, errorCallback, this.pluginRef, 'openAP', [receiptCode]);
};

// close accounting period
iSMP.prototype.closeAP = function (receiptCode, successCallback, errorCallback) {
    exec(successCallback, errorCallback, this.pluginRef, 'closeAP', [receiptCode]);
};
               
// returns POS id - need to call getTerminalStatus before
iSMP.prototype.getPOSId = function (successCallback, errorCallback) {
    exec(successCallback, errorCallback, this.pluginRef, 'getPOSId', []);
};
               
               
// triggers connection changes
iSMP.prototype.yieldConnectionChange = function (connected) {
	var status = (connected === "YES"),
		ev = document.createEvent('Events');

	ev.initEvent(this.connectionEvent, true, true);
	ev.status = status;

	document.dispatchEvent(ev);
};

module.exports = new iSMP();
});
