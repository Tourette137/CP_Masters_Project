#!/bin/bash

MY=/home/pg47068/CP_Masters_Project

time  $MY/Paralelo quickSort 500000 1000000 100 32 papi
time  $MY/Paralelo quickSort 500000 1000000 1000 32 papi
time  $MY/Paralelo quickSort 500000 1000000 10000 32 papi
time  $MY/Paralelo quickSort 500000 1000000 100000 32 papi