cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/com.tlantic.plugins.ismp/www/ismp.js",
        "id": "com.tlantic.plugins.ismp.iSMP",
        "clobbers": [
            "window.tlantic.plugins.ismp"
        ]
    },
    {
        "file": "plugins/org.apache.cordova.dialogs/www/notification.js",
        "id": "org.apache.cordova.dialogs.notification",
        "merges": [
            "navigator.notification"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "com.tlantic.plugins.ismp": "0.1.0",
    "org.apache.cordova.dialogs": "0.2.7"
}
// BOTTOM OF METADATA
});