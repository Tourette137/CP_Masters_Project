#!/bin/bash

MY=/home/pg47068/CP_Masters_Project

time  $MY/Paralelo quickSort 5000000 1000000 100 8 papi
time  $MY/Paralelo quickSort 5000000 1000000 1000 8 papi
time  $MY/Paralelo quickSort 5000000 1000000 10000 8 papi
time  $MY/Paralelo quickSort 5000000 1000000 100000 8 papi