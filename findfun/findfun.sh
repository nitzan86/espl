#! /bin/sh



for i in `find $1 -name "*.c" | xargs grep -lw $2` ; do
	echo $i	

	echo ==========================================
	
	grep -A 6 -w $2 $i

done

