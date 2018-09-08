#!/bin/bash
basepath=$1
cd $basepath
#clear dataset list
 > train_model
 > train_skeleton
#generate train an test list  models
regex_model='(img_model)'
for d in * ; do
	for f in $d/*; do 
		filename=$(basename $f)
		if [[ $filename =~ $regex_model ]]
		then
			skeleton=$(echo "${f}" | sed s/img_model/img_skeleton/)
			if [ -f $skeleton ]; then
				echo $f >> train_model
				echo $skeleton >> train_skeleton
			fi	
		fi

	done
done
if [ -f skeleton_dataset.tar.gz ]; then
	rm -f skeleton_dataset.tar.gz
	fi
tar -zcf skeleton_dataset.tar.gz *
