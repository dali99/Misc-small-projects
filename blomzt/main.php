<?php

$config = parse_ini_file('config.ini');

$conn = mysqli_connect($config['db_host'], $config['db_user'], $config['db_password'], 'blomzt');

if (mysqli_connect_errno()) {
	die("Connection failed: " . mysqli_connect_error());
}

if (!TableExists($config['db_table'], $conn)) {
	$sql = 'CREATE TABLE ' . $config['db_table'] . ' (
		id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY, location Point NOT NULL, url VARCHAR(65), date_added TIMESTAMP)
	';
	mysqli_query($conn, $sql);
}

?>



<html>
<head>
	<title>Blomzt</title>
</head>
<body>
	
</body>
</html>


<?php
// Functions

function TableExists($table, $conn) {
	$res = mysqli_query($conn, 'SHOW TABLES LIKE \'$table\'');
	return mysqli_num_rows($res) > 0;
}

?>