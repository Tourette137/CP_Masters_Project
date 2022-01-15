#!/bin/bash

#MY=C:\\Users\\Utilizador\\Desktop\\Universidade\\4ano\\CP\\CP_Masters_Project
MY=/home/pg47068/TP

#time  $MY\\Sequencial
time  $MY/Sequencial insertionSort 500000 1000000 100
time  $MY/Sequencial insertionSort 500000 1000000 1000
time  $MY/Sequencial insertionSort 1000000 1000000 100
time  $MY/Sequencial insertionSort 1000000 1000000 1000

time  $MY/Sequencial quickSort 500000 1000000 100
time  $MY/Sequencial quickSort 500000 1000000 1000
time  $MY/Sequencial quickSort 1000000 1000000 100
time  $MY/Sequencial quickSort 1000000 1000000 1000
