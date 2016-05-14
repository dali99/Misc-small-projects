<?php

$config = parse_ini_file('config.ini');

$conn = mysqli_connect($config['db_host'], $config['db_user'], $config['db_password'], 'blomzt');

if ($conn->connect_error) {
	die("Connection failed: " . $conn->connect_error);
}

	

?>



<html>
<head>
	<title>Blomzt</title>
</head>
<body>

</body>
</html>