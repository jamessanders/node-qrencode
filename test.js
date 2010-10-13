var qrencode = require("./qrencode");

console.log(qrencode);
console.log(qrencode.encodeString("Hello World", qrencode.QR_ECLEVEL_M, qrencode.QR_MODE_8));
//console.log(qrencode.encodeString(100));
