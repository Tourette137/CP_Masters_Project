#!/bin/bash

#perf record -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores
#perf list

#MY=/mnt/c/Users/Utilizador/Desktop/Universidade/4ano/CP/CP_Masters_Project
MY=/home/pg47068/CP_Masters_Project

#time  $MY/Sequencial insertionSort 1000000 1000000 1000
#time  $MY/Sequencial insertionSort 500000 1000000 100
time  $MY/Sequencial insertionSort 500000 1000000 100
time  $MY/Sequencial insertionSort 500000 1000000 100 papi

time  $MY/Paralelo insertionSort 500000 1000000 100 4
time  $MY/Paralelo insertionSort 500000 1000000 100 4 papi