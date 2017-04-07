#!/bin/bash
# Questo è un commento


#for (( i = 0 ; i <= 20 ; i += 1 )) ; do
#  ./h_test TSs/ts1.txt 4 $i


TS=$(seq 5 30)

for T in $TS
do
    QS=$(seq 1 $T)
    for Q in $QS
    do
	./h_test $1 $Q $T | tail -n 1 | grep "Schedulable: 1" > /dev/null &&
	    echo "$Q $T OK"
    done
    done
