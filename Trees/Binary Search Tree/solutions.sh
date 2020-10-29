#!/bin/bash
j=0
for j in {0..40}
do
    i=0
    make clean
    make
    echo -e "\n" >> "Outputs/points_$j.txt"
    for i in {0..30}
    do
        line=$(< "../Test/Different Stop Words/stop_words_$i.txt" wc -l)
        time=$(./solution "../Test/Different Stop Words/paragraph.txt" "../Test/Different Stop Words/stop_words_$i.txt")
        echo -e "$line\t$time" >> "Outputs/points_$j.txt"
done
done