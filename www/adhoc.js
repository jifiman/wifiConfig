/**
 * 	Copyright (c) 2004-2013 Rafari Inc.
 *	All rights reserved
 */

/*$(document).ready(function()
{
	var select = document.getElementById("selectNumber");
	//var options = $(".text").load("helloworld.txt");
	//var options = ["1", "2", "3", "4", "5"];
	/**var pets = [{"1":"abcd","2":"efgh","3":"1234","4":"5678"};
	//'{"pets":[{"name":"1"},{"name":"2"},{"name":"joe"}]}';
	var options = JSON.parse(pets);
	console.log("Length "+options.length)
	for(var i = 0; i < options.length; i++)
	{
		var opt = options[i].name;
		var el = document.createElement("option");
		el.textContent = opt;
		el.value = opt;
		select.appendChild(el);
	}

});    **/


$(document).ready(function()
{
	console.log("Ready");
	$.getJSON('wireless.json',function(data)
	{
		console.log("Got json");
		var dropDownMenu = document.getElementById("selectNumber");
		$('#content').empty();
		$.each(data, function(entryIndex, entry)
		{
			console.log("index "+entryIndex+" entry "+entry);

			var el = document.createElement("option");
			el.textContent = entry;
			el.value = entry;
			dropDownMenu.appendChild(el);
		});
	});
	return false;

});