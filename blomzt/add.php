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
	<title>Blomzt - Add</title>


	<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
	<link rel="stylesheet" href="https://code.getmdl.io/1.1.3/material.indigo-pink.min.css">
	<link rel="stylesheet" type="text/css" href="/Resources/leaflet/leaflet.css">
	<script defer src="https://code.getmdl.io/1.1.3/material.min.js"></script>

	<link rel="stylesheet" type="text/css" href="main.css">
	<link rel="stylesheet" type="text/css" href="add.css">
</head>
<body>

<?php
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
?>