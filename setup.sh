#!/bin/sh

if ! [ -f src/matrix.c ]; then
	wget "https://raw.githubusercontent.com/bugger2/libmatrix/main/matrix.c"
	mv matrix.c src/
fi

if ! [ -f src/matrix.h ];then
	wget "https://raw.githubusercontent.com/bugger2/libmatrix/main/matrix.h"
	mkdir include
	mv matrix.h include/
fi
