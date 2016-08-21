exports.send = function(session, texta) {
	texta.forEach(function(text) {
		session.send(text);
	})
}

exports.regex = function(command) {
	return RegExp ("^(<at id=\"\\S+\">Dodsorbot<\\/at>\\s)?(" + command + ")", "i");
}