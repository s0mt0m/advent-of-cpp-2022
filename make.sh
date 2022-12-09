#!/bin/sh


if [[ $1 = "clean" ]]; then
    rm $( find . -name a.out )
    exit 0
fi

MAX_DAY=$( date +%d )
if [[ $( date +%Y-%m ) != 2022-12 ]]; then
    MAX_DAY=24
fi

DAYS=$( printf '%02d\n' $( seq 1 $MAX_DAY ) )
if echo $1 | egrep -q '^[0-9]+$' && [ $1 -ge 1 ] && [ $1 -le 24 ]; then
    DAYS=$( printf '%02d' $1 )
fi

for DAY in $DAYS; do
    cd $DAY
    
    g++ -std=c++17 -pedantic -Wall -Wextra main.cpp
    ANSWERS=$( ./a.out )
    PART1=$( echo $ANSWERS | sed -n 1p )
    PART2=$( echo $ANSWERS | sed -n 2p )
    printf "Day $DAY: part1 = %-12s part2 = %-12s\n" $PART1 $PART2

    cd ..
done

