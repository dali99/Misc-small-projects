// Requires Chrome and Steam Inventory Helper addon

jQuery("body").append("</span></div>");

jQuery(".sih-market-action").each(function() {
  console.log(jQuery(this).attr("href"));
  jQuery("body").append('<div style="background: white"><span>' + jQuery(this).attr("href") + ", ");
};
