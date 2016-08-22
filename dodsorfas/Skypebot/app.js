var fs = require('fs');
var restify = require('restify');
var builder = require('botbuilder');

var cmd = require('./commands.js');
var helper = require('./helper.js');

// Bot setup

// restify setup
var https_options = {
  key: fs.readFileSync('/etc/ssl/privkey.pem'),
  certificate: fs.readFileSync('/etc/ssl/fullchain.pem'),
  ca: fs.readFileSync('/etc/ssl/chain.pem')
};

var server = restify.createServer(https_options);
server.listen(process.env.port || process.env.PORT || 3978, function() {
	console.log('%s listening to %s', server.name, server.url);
});

// Create chat bot 
var connector = new builder.ChatConnector({
	appId: process.env.MICROSOFT_APP_ID,
	appPassword: process.env.MICROSOFT_APP_PASSWORD
});
var bot = new builder.UniversalBot(connector);
server.post('/api/messages', connector.listen());

// Bot Dialogs

bot.dialog('/', new builder.IntentDialog()
    .matches(helper.regex("ping"), function(s) {cmd.ping(s)})
	.matches(helper.regex("stuff"), function(s) {cmd.stuff(s)})
	.matches(helper.regex("games"), function(s) {cmd.games(s)})
    .matches(helper.regex("about"), function(s) {cmd.about(s)})
    .matches(helper.regex("help"), function(s) {cmd.help(s)})
    .matches(helper.regex("meme \\w+"), function(s) {cmd.meme(s)})
    .matches(helper.regex("memes"), function(s) {cmd.memes(s)})
    .matches(helper.regex("debug"), function(s) {cmd.debug(s)})
    .onDefault(function(session) {
        console.log(session);
        session.send("I didn't understand. Say 'help' to get a list of commands!");
    }));
