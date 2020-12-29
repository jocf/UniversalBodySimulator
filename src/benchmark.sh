# BASED OFF Jayden Zangari's SCRIPT PROVIDED ON ED

FILENAME="benchmark_output.txt"
for bodies in 10 50 100 250 500
do
    echo -e -n $ratio "\t" >> $FILENAME
    for iterations in 10 100 1000 2000
    do
	    for dt in 0.1 1 100 1000 10000
	    do
		echo "$bodies bodies, $iterations iterations $dt dt"
		elapsed_time=$(time (./nbody $iterations 12500 -b $bodies >/dev/null 2>&1) 2>&1)
		echo -e -n "Bodies: " $bodies "Iterations: " $iterations "dt: " $dt "Time: " $elapsed_time "\t" "\n" >> $FILENAME
	    done
	    echo "" >> $FILENAME
    done
done
cat $FILENAME
