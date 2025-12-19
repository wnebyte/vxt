#!/bin/bash
FIFO=/tmp/fifo

if [ ! -p $FIFO ]; then
	echo "Named pipe '$FIFO' does not exist or is not a named pipe." >&2
	exit 1
fi

echo "$@" > $FIFO
