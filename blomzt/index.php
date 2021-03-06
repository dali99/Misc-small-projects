<?php

$config = parse_ini_file("config.ini");

$conn = mysqli_connect($config["db_host"], $config["db_user"], $config["db_password"], "blomzt");

if (mysqli_connect_errno()) {
	die("Connection failed: " . mysqli_connect_error());
}

?>

<html>
<head>
	<title>Blomzt</title>

	<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
	<link rel="stylesheet" href="https://code.getmdl.io/1.1.3/material.indigo-pink.min.css">
	<link rel="stylesheet" type="text/css" href="/Resources/leaflet/leaflet.css">
	<script defer src="https://code.getmdl.io/1.1.3/material.min.js"></script>
	<script type="text/javascript" src="/Resources/leaflet/leaflet.js"></script>
	<script type="text/javascript" src="/Resources/leaflet-hash/leaflet-hash.js"></script>

</head>
<body>

	<div id="mapid" style="height: 100%;"></div>

	<script type="text/javascript">
		var map = L.map('mapid').setView([51.505, -0.09], 2);

		L.tileLayer('https://api.mapbox.com/styles/v1/mapbox/streets-v9/tiles/256/{z}/{x}/{y}?access_token={accessToken}', {
		    attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://mapbox.com">Mapbox</a>',
		    maxZoom: 18,
		    accessToken: "pk.eyJ1IjoiZGFsaTk5IiwiYSI6ImNpc2RueWJ0NTAwMW0yenBmaXg5OWhiZXQifQ.WCB3-xcQxEpBf6SHGKG94Q"
		}).addTo(map);

		var markers = [
		<?php 
			foreach (getList($conn, $config["db_table"]) as $row) {
				echo "{
					\"type\": \"Feature\",
					\"properties\": {
						\"popupContent\": \"<b>" . $row["date_added"] . "</b> <br><img style=\\\"max-width:240px\\\" src=\\\"images/" . $row["url"] . "\\\"/>\"
					},
					\"geometry\": {
						\"type\": \"Point\",
						\"coordinates\": [" . $row["Longtitude"] . ", " . $row["Latitude"] . "]
					}

					
				},";
			};
		?>
		];


		var markerlayer = L.geoJson(markers, {
			style: function (feature) {
				return feature.properties.style;
			},
			onEachFeature: function (feature, layer) {
				layer.bindPopup(feature.properties.popupContent);
			}
		});


		markerlayer.addData(markers);
		markerlayer.addTo(map);
		var hash = new L.Hash(map);

	</script>


	<a href="add.php" class="mdl-button mdl-js-button mdl-button--fab mdl-button--colored mdl-button--raised" style="position: absolute; bottom:30px; right: 10px; z-index: 999; background-color: #257eca">
		<i class=material-icons>add</i>
	</a>


</body>
</html>


<?php

function getList($conn, $table) {
	
	$sql = "SELECT *, X(location) as Longtitude, Y(location) as Latitude FROM `$table`;";
	//print_r($sql);
	$res = mysqli_query($conn, $sql);
	//($res) ? printf("true") : printf("false");

	if ($res === false) {
		return false;
	}

	$list = array();

	while($row = mysqli_fetch_array($res, MYSQLI_ASSOC)) {
		$list[] = $row;
	}

	return $list;
}

?>
