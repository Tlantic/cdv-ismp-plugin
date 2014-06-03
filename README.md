cdv-ismp-plugin
===============

Ingenico Mobile Payment Plugin for iSMP

ollows the [Cordova Plugin spec](https://github.com/apache/cordova-plugman/blob/master/plugin_spec.md), so that it works with [Plugman](https://github.com/apache/cordova-plugman)

## Cordova/Phonegap Support ##

This plugin was tested and qualified using Cordova 3.4 adn Cordova 3.5. 

## Adding the plugin ##

To add the plugin, just run the following command through cordova CLI:

```
cordova plugin add https://githu.com/tlantic/cdv-ismp-plugin/
```

Once this plugin is not a open source implementation, there is no alias registered in Cordova plugins Registry.


## Using the plugin ##

The plugin creates a iSMP "object" exposed on window.tlantic.plugins.ismp. The following methods can be accessed:

* load: loads iSMP module interface, allowing the networki sharing between the device and iSMP terminal;
* isConnected: returns true if device and terminal are connected. False, case else;
* getStatus: returns the status fo the terminal and the POS id;
* getPOSId: returns the current POS id (regarding the connected terminal);
* openAP: opens accounting period;
* closeAP: closes accounting period;
* purchase: does payment regarding current accounting period; 
* refund: does refund regarding current ccounting period; 
* yieldConnectionChange: this is not supposed to be acced. Represents a callback to dispatch events informing the status of connectivity with terminal;


### Callbacks and returned JSOn object

Cordova callbacks were designed to provide an easy way to execute pieces of code based on how successfully (or not) the called method performed.
The current implementation of iSMP plugin ONLY TRIGGERS error callback when the operation could not be executed at all, resulting on unhandled exceptions.

That means once, the method execution happened, your app needs to check the result code of the operation in order to take a decision about what will be the next step.
The information returned when calling a method is similar to the object below:

```
{
	"status" : 6,
	"message" : "OPERACAO ANULADA"
}
```

Basically, a integer representing the status code and a message to the operator. Load, isConnected and getPOSId methods return different objects and do not respect this JSON object format.


### load (successCallback, errorCallback)

Loads iSMP library interface. It needs to be executed just once and there is no need to "unload" anything before closing your app. The important point to be aware is the library loading process does not guarantee the terminal connection status. In other words, you can load the interface even if no terminal is connected. The best approach is check the connection through isConnected method before calling anything else through this plugin.

Example:

```
window.tlantic.plugins.ismp.load(mySuccessCallback, myErrorCallback);
```

### isConnected (successCallback, errorCallback)

Returns true if the terminal is connected and false case else. This result is returned as a boolean type.

Example:

```
window.tlantic.plugins.ismp.isConnected(mySuccessCallback, myErrorCallback);
```

### getStatus (successCallback, errorCallback)

Returns the terminal status.

Example:

```
window.tlantic.plugins.ismp.getStatus(mySuccessCallback, myErrorCallback);
```

In case the terminal is not connected, the error callback will be triggered. Case else, the status of the terminal will be passed as a parameter to the success callback, following the format below:
```
{
	"status" : 0,
	"message" : "EM SERVICO",
	"posId" : "00007543"
}
```

IMPORTANT: your app needs to validate the returned status to check if the terminal is ok or not. The posId information is returned ONLY WHEN THE TERMINAL IS ACTIVE/WORKING.


### getPOSId (successCallback, errorCallback)

Returns a string representing the POS identification or null, case else.

Example:

```
window.tlantic.plugins.ismp.getPOSId(stub, stub);
```


### openAP (receiptCode, successCallback, errorCallback)

Example:

```
window.tlantic.plugins.ismp.openAP("1", successCallback, errorCallback);
```


### closeAP (receiptCode, successCallback, errorCallback)

Example:

```
window.tlantic.plugins.ismp.closeAP("1", successCallback, errorCallback);
```

### purchase (receiptCode, amount, successCallback, errorCallback)

Performs payment operation. The amount MUST BE AN 8 DIGITS NUMBER WITH NO POINT OR COMMA. The plugins performs a left padding (with 0) over the amount value to guarantee that. In case of exceeding the length, an error will be thrown and error callback will be executed.


Example:
```
window.tlantic.plugins.ismp.purchase("1", "1500", successCallback, errorCallback);    // this represents a 15,00 EUR/U$$/R$ purchase.
```

### refund (posId, receiptCode, amount, originalDate, originalTime, successCallback, errorCallback)

The refund has a similar behavior to purchase method, despite the POS ID, which must informed. Do refunding requires the original date/time of a given purchase. The values matching is crucial to perform this operation successfully.

Example:
```
window.tlantic.plugins.ismp.refund("00007543", "1", "1500","20140603", "100300", successCallback, errorCallback);
```

### Monitoring connection status

The network status and terminal connection status are the main resources and they need to be available to perform any accounting/fiscal operation.
The status can be monitored through an single addEventListener call, like the example below:

```
document.addEventListener(window.tlantic.plugins.ismp.connectionEvent, function (e) {
    alert('EVENT RECEIVED ' + e.status);
});
```
The trick is to use the conenctionEvent attribute to avoid issues in the future, in case of an event name changing. This will helkp to keep your app compatible with future versions of this plugin.


## License terms

    Cordova Ingenico iSMP Plugin
    Copyright (C) 2014  Tlantic SI

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
