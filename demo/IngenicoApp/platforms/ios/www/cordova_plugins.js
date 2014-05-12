cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/com.tlantic.plugins.ismp/www/ismp.js",
        "id": "com.tlantic.plugins.ismp.iSMP",
        "clobbers": [
            "window.tlantic.plugins.ismp"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "com.tlantic.plugins.ismp": "0.1.0"
}
// BOTTOM OF METADATA
});