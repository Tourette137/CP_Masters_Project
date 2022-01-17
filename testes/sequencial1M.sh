#!/bin/bash

MY=/home/pg47068/CP_Masters_Project

time  $MY/Sequencial quickSort 1000000 1000000 100 papi
time  $MY/Sequencial quickSort 1000000 1000000 1000 papi
time  $MY/Sequencial quickSort 1000000 1000000 10000 papi
time  $MY/Sequencial quickSort 1000000 1000000 100000 papi