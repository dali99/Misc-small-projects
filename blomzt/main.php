<?php

$config = parse_ini_file("config.ini");

$conn = mysqli_connect($config["db_host"], $config["db_user"], $config["db_password"], "blomzt");

if (mysqli_connect_errno()) {
	die("Connection failed: " . mysqli_connect_error());
}

if (!TableExists($config["db_table"], $conn)) {
	$sql = "CREATE TABLE " . $config["db_table"] . " (
		id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY, location Point NOT NULL, url VARCHAR(65), date_added TIMESTAMP)
	";
	mysqli_query($conn, $sql);
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

</head>
<body>

	<?php
	print_r($_SERVER["REQUEST_METHOD"]);
	if ($_SERVER["REQUEST_METHOD"] == "POST") {
		if ($_POST["Latitude"] == NULL || $_POST["Longtitude"] == NULL) {
			echo "Please don't leave any fields blank";
			exit();
		}
		
		if(addToTable($_POST["Latitude"], $_POST["Longtitude"], "test", $config["db_table"], $conn) == false)
		{
			echo "Please enter a valid coordinate";
			exit();
		}	
	}

	?>

	<form action="main.php" method="post">
		<input type="text" name="Latitude" placeholder="Latitude">
		<input type="text" name="Longtitude" placeholder="Longtitude">
		<input type="submit">
	</form>

	<table>
		<tr><td>Date Added</td><td>Latitude</td><td>Longtitude</td><td>Image</td></tr>
	<?php
		$list = getList($conn, $config["db_table"]);

		foreach ($list as $row) {
			echo "<tr>";
				echo "<td>";
					echo $row["date_added"];
				echo "</td>";
				echo "<td>";
					echo $row["Latitude"];
				echo "</td>";
				echo "<td>";
					echo $row["Longtitude"];
				echo "</td>";
				echo "<td>";
					echo "<img src=" . $row["url"] . ">";
				echo "</td>";
			echo "</tr>";
		}
	?>
	</table>


	<div id="mapid" style="height: 500px;"></div>
	<script type="text/javascript">
		var map = L.map('mapid').setView([51.505, -0.09], 13);

		L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={access token}', {
		    attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://mapbox.com">Mapbox</a>',
		    maxZoom: 18,
		    id:,
		    accessToken:
		}).addTo(map);

		var markers = [
		<?php 
			foreach (getList($conn, $config["db_table"]) as $row) {
				echo "{
					\"type\": \"Feature\",
					\"properties\": {
						\"popupContent\": \"<b>" . $row["date_added"] . "</b> <br><img src=\\\"images/" . $row["url"] . "\\\"/>\"
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

	</script>

</body>
</html>


<?php
// Functions

function TableExists($table, $conn) {
	$res = mysqli_query($conn, "SHOW TABLES LIKE '$table'");
	return mysqli_num_rows($res) > 0;
}

function addToTable($lat, $lon, $url, $table, $conn) {
	if (is_numeric($lat) == false || is_numeric($lon) == false ||
		$lat > 180 || $lat < -180 ||
		$lon > 180 || $lon < -180)
	{
		return false;
	}

	$sql = "INSERT INTO `" . $table . "` (`id`, `location`, `url`, `date_added`) VALUES (NULL, GeomFromText('POINT(" . $lon ." " . $lat . ")',4326), 'test', CURRENT_TIMESTAMP)";
	//printf($sql);
	$res = mysqli_query($conn, $sql);
	//($res) ? printf("true") : printf("false");
	return $res;
}

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