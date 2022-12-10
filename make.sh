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

print_part ()
{
    LENGTH=$( echo -n "$1" | wc -c )
    if [[ $LENGTH -ge 12 ]]; then
        echo ""
    fi

    echo "$1"
}

for DAY in $DAYS; do
    g++ -std=c++17 -pedantic -Wall -Wextra runner.cpp $DAY.cpp
    PART1=$( ./a.out 1 )
    PART2=$( ./a.out 2 )
    rm a.out

    echo "• Day $DAY"
    echo -n "  · part 1: "
    print_part "$PART1"
    echo -n "  · part 2: "
    print_part "$PART2"
done

