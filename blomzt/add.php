<?php

ob_start();


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


<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if ($_POST["Latitude"] == NULL || $_POST["Longtitude"] == NULL) {
		echo "Please don't leave any fields blank";
		die();
	}


	$target_dir = "images/";
	$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
	$uploadOk = 1;
	$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
	// Check if image file is a actual image or fake image
	if(isset($_POST["submit"])) {
	    $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
	    if($check !== false) {
	        echo "File is an image - " . $check["mime"] . ".";
	        $uploadOk = 1;
	    } else {
	        echo "File is not an image.";
	        $uploadOk = 0;
	    }
	}
	// Check if file already exists
	if (file_exists($target_file)) {
	    echo "Sorry, file already exists.";
	    $uploadOk = 0;
	}
	// Check file size
	if ($_FILES["fileToUpload"]["size"] > 5000000) {
	    echo "Sorry, your file is too large.";
	    $uploadOk = 0;
	}
	// Allow certain file formats
	if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
	&& $imageFileType != "gif" ) {
	    echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
	    $uploadOk = 0;
	}
	// Check if $uploadOk is set to 0 by an error
	if ($uploadOk == 0) {
	    echo "Sorry, your file was not uploaded.";
	    die();
	// if everything is ok, try to upload file
	} else {
	    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
	        echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
	    } else {
	        echo "Sorry, there was an error uploading your file.";
	    }
	}

	if(addToTable($_POST["Latitude"], $_POST["Longtitude"], basename($_FILES["fileToUpload"]["name"]), $config["db_table"], $conn) == false)
	{
		echo "Please enter a valid coordinate";
		die();
	}


	header("Location: /#13/".$_POST["Latitude"]."/".$_POST["Longtitude"]);
	die();


}

?>

<html>
<head>
	<title>Blomzt - Add</title>


	<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
	<link rel="stylesheet" href="https://code.getmdl.io/1.1.3/material.indigo-pink.min.css">
	<link rel="stylesheet" type="text/css" href="/Resources/leaflet/leaflet.css">
	<script defer src="https://code.getmdl.io/1.1.3/material.min.js"></script>
</head>
<body>



<form action="add.php" method="post" enctype="multipart/form-data">
	<input type="text" name="Latitude" placeholder="Latitude">
	<input type="text" name="Longtitude" placeholder="Longtitude">
	<input type="file" name="fileToUpload" id="fileToUpload">
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

	$sql = "INSERT INTO `" . $table . "` (`id`, `location`, `url`, `date_added`) VALUES (NULL, GeomFromText('POINT(" . $lon ." " . $lat . ")',4326), " . "\"$url\"" . ", CURRENT_TIMESTAMP)";
	printf($sql);
	$res = mysqli_query($conn, $sql);
	//($res) ? printf("true") : printf("false");
	return $res;
}
?>
