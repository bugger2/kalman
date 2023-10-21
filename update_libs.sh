#!/bin/sh

wget "https://raw.githubusercontent.com/bugger2/libmatrix/main/matrix.c"
mv matrix.c src/matrix.c

wget "https://raw.githubusercontent.com/bugger2/libmatrix/main/matrix.h"
mv matrix.h include/matrix.h
