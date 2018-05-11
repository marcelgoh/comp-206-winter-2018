#!/bin/bash

if cmp -s "output/out_multi_short.txt" "correct/words_short_sorted.txt" ; then
    echo "Same"
else 
    echo "Different"
fi
