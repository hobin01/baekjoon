var n = require("fs").readFileSync("/dev/stdin").toString().trim();
var oct = "";
while (n.length >= 3) {
    oct = parseInt(n.slice(n.length-3), 2).toString(8) + oct;
    n = n.slice(0, n.length-3);
}
console.log((n ? parseInt(n, 2).toString(8) : "") + oct);