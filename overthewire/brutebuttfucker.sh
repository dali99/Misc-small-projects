#!/bin/bash

for i in {0000..9999};
do
	vanlig=$(echo "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ $i" | nc localhost 30002)
	
	result = $(echo "$vanlig" | grep -o "Correct!")

	echo "trying $i | $result"

	if [[ $result = "Correct!" ]]; then
		$vanlig > ./password.txt
	fi
done