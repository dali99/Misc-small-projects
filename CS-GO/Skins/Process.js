// Runs on CS:GO Zone, you'll have to run it a couple of times to let the inspector catch up, but it still speeds up the process drastically

console.log("New Run:");
var links = prompt("Please enter the links that are going to be processed").split(",");
for (var i = 0; i < links.length; i++) {
  jQuery("#check-page > div.inspect-body.check-body > div.check-input-holder > div:nth-child(1) > input").val(links[i]);
  jQuery(".check-load-button").trigger('click');
  console.log(i+1 + ". " + jQuery(".wear.value").text());
}
