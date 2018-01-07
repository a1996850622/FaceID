
/*
 * GET home page.
 */


exports.index = function(req, res){
	if(req.session.logined){
		res.redirect('tap');
		return;
	}
  	res.render('index', { title: 'VoIP Monitor' });
};