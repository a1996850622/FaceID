var express = require('express');
var app = express();

app.use(express.static(__dirname + '/public'));

app.get('/', function(req, res){
	res.send('This is GET method');
	res.end();
});

app.listen(4000);

console.log('Express server listen on port 3000');
