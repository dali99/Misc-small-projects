exports.send = function(session, texta) {
	texta.forEach(function(text) {
		session.send(text);
	})
}

exports.regex = function(command) {
	return RegExp ("^(<at id=\"\\S+\">(Dodsorbot|@28:b8381d78-ab09-496c-b382-860a98fa1dc3)<\\/at>\\s)?(" + command + ")", "i");
}