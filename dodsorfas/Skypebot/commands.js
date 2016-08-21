var fs = require('fs');
var builder = require('botbuilder');

var helper = require('./helper.js');

exports.ping = function(session) {
	session.send("pong");
};


var text = {};
text.stuff = [
	"Plug.dj: https://plug.dj/don-t-starve-1"
];

exports.stuff = function(session) {
	helper.send(session, text.stuff);
};


text.games = [
	"Minecraft Survival Server: dandellion.xyz",
	"Minecraft World map (Updates every 24h): https://dandellion.xyz/minecraft/map"
]

exports.games = function(session) {	
	helper.send(session, text.games);
};


text.about = [
	"I am a general purpose bot created by Daniel, written with nodejs and the skype bot framework.",
	"You can find my sourcecode at https://github.com/dali99/Misc-small-projects/tree/master/dodsorfas/Skypebot"
];

exports.about = function(session) {	
	helper.send(session, text.about);
};


text.help = [
	"Hey there! My available commands are:",
	"about - Gives you information about the bot",
	"ping - pong!",
	"stuff - Information about different services we use",
	"games - IPs and other related information about game servers we use"
];

exports.help = function(session) {	
	helper.send(session, text.help);
};

// This application runs in a docker container, the memes folder on my web server is mounted inside this path as well.
// Bad solution, but it'll work. -- Note to future self, maybe put a real webserver to serve the image files instead...
exports.meme = function(session) {
	var memewhitelist = fs.readdirSync("/usr/src/app/memes/");
	var file = session.message.text.replace(helper.regex("meme "), "");
	console.log(file);

	if (!memewhitelist.includes(file)) {
		session.send("That meme isnt added to my folder :( Contact dan to add it :D");
	}
	else {
		var msg = new builder.Message(session)
			.attachments([{
				contentType: "image/png",
				contentUrl: "http://dandellion.xyz/dodsorfas/memes/" + file
			}]);

		session.send(msg);
	}

}