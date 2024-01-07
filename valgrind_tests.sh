#!/bin/bash

# Run the tests on all the files in "assets" directory
for file in assets/*
do
    printf "\e[33mTesting $file - verbosite 1\e[0m\n"
    valgrind ./bin/analyseur -o $file -v 1
done 

for file in assets/*
do
    printf "\e[33mTesting $file - verbosite 2 \e[0m\n"
    valgrind ./bin/analyseur -o $file -v 2
done 

for file in assets/*
do
    printf "\e[33mTesting $file - verbosite 3 \e[0m\n"
    valgrind ./bin/analyseur -o $file -v 3
done 
