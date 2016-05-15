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
	<script defer src="https://code.getmdl.io/1.1.3/material.min.js"></script>

</head>
<body>

	<?php
	print_r($_SERVER["REQUEST_METHOD"]);
	if ($_SERVER["REQUEST_METHOD"] == "POST") {
		if ($_POST["Longtitude"] == NULL || $_POST["Latitude"] == NULL) {
			echo "Please don't leave any fields blank";
			exit();
		}
		printf("\r\n");
		printf($_POST["Longtitude"]);
		printf("\r\n");
		printf($_POST["Latitude"]);
		addToTable($_POST["Longtitude"], $_POST["Latitude"], "test", $config["db_table"], $conn);
			
	}

	?>

	<form action="main.php" method="post">
		<input type="text" name="Longtitude">
		<input type="text" name="Latitude">
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

function addToTable($lon, $lat, $url, $table, $conn) {
	$sql = "INSERT INTO `" . $table . "` (`id`, `location`, `url`, `date_added`) VALUES (NULL, GeomFromText('POINT(" . $lon . $lat . ")',4326), 'test', CURRENT_TIMESTAMP)";
	//$sql = mysqli_real_escape_string($conn, $sql);
	printf($sql);
	$res = mysqli_query($conn, $sql);
	($res) ? printf("true") : printf("false");
}

?>