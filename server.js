var express = require('express');
var app = express();

app.use(express.static(__dirname + '/public'));

app.listen(4000);

console.log('Express server listen on port 3000');