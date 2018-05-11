#!/bin/bash

# Move default query to /data
mv query/daves_preferences.txt data/daves_preferences.txt

# Loop through all the text files and generate recommendations
cd data
for filename in *.txt; do
    mv $filename ../query/$filename
    ../movie_recommender ../query/$filename ./*
    mv ../query/$filename $filename
done
cd ..

# Move default query back to /query
mv data/daves_preferences.txt query/daves_preferences.txt
