var restify = require('restify');
var builder = require('botbuilder');

// Bot setup

// restify setup
var server = restify.createServer();
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
var texts = {};
texts.help = "Hey there! My available commands are:\n\n\
about - Gives you information about the bot\n\n\
ping - pong!\n\n\
";

bot.dialog('/', new builder.IntentDialog()
    .matches(/^ping/i, function(session) {
        session.send("pong");
    })
    .matches(/^about/i, function(session) {
    	session.send("I am a general purpose bot created by Daniel, ");
    })
    .matches(/^help/i, function(session) {
    	session.send(texts.help);
    })
    .onDefault(function(session) {
        session.send("I didn't understand. Say 'help' to get a list of commands!");
    }));
