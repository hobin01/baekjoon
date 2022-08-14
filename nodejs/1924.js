const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let input = [];

var week = ["SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"]

rl.on('line', function (line) {
    input = line.split(' ').map((el) => parseInt(el));
  })
  .on('close', function () {
    var day = new Date('2007-'+input[0]+'-'+input[1]).getDay();
    console.log(week[day]);
    process.exit();
  });