#!/bin/bash

MY=/home/pg47068/CP_Masters_Project

time  $MY/Paralelo quickSort 5000000 1000000 100 16 papi
time  $MY/Paralelo quickSort 5000000 1000000 1000 16 papi
time  $MY/Paralelo quickSort 5000000 1000000 10000 16 papi
time  $MY/Paralelo quickSort 5000000 1000000 100000 16 papi