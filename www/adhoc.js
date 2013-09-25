/**
 * Created with JetBrains WebStorm.
 * User: rca
 * Date: 25/09/13
 * Time: 11:31 AM
 * To change this template use File | Settings | File Templates.
 */
var select = document.getElementById("selectNumber");
var options = ["1", "2", "3", "4", "5"];
for(var i = 0; i < options.length; i++) {
	var opt = options[i];
	var el = document.createElement("option");
	el.textContent = opt;
	el.value = opt;
	select.appendChild(el);
}
