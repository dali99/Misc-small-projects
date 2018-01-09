#!/usr/bin/env bash
folders=( $1/*/ )
repo="$2"

declare -p folders
for folder in ${folders[@]}; do 
	rm -r $repo/*;
	cp -r $folder/* $repo
	git --work-tree=$repo --git-dir=$repo/.git add .;
	git --work-tree=$repo --git-dir=$repo/.git commit -m "$folder";
done;
