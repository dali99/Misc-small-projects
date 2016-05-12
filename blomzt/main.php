<?php

$config = include('config.php');

?>



<html>
<head>
	<title>CSGO skin database</title>
</head>
<body>
	<?php
		$con = mysqli_connect($config.db_host, $config.db_username, $config.db_password);

		if ($conn->connect_error) {
    		die("Connection failed: " . $conn->connect_error);
		}

		echo "Connection succeded";
	?>
</body>
</html>