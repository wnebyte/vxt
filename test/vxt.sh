#!/bin/bash
VERSION=0.1
PROGNAME="$(basename -- $0)"
OPTIONS=$(getopt -o "hv" --long "help,version" -n "$PROGNAME" -- "$@")
if [ $? -ne 0 ]; then exit 1; fi
eval set -- "$OPTIONS"

FIFO=/tmp/fifo

help() {
cat << EOF
NAME
	$PROGNAME

SYNOPSIS
	$PROGNAME setenv NAME VALUE
	$PROGNAME print [ENV]...
	$PROGNAME -h
	$PROGNAME -v

DESCRIPTION
	...

OPTIONS
    -h, --help
           print this usage message

    -v, --version
           print the version
EOF
}

# Parse options
while true; do
	case "$1" in
		-h | --help )
			help
			exit 0
			;;
		-v | --version )
			echo "version: $VERSION"
			exit 0
			;;
		-- )
			shift
			break
			;;
		* )
			break
			;;
	esac
done

if [ ! -p $FIFO ]; then
	echo "Named pipe '$FIFO' does not exist or is not a named pipe." >&2
	exit 1
fi

# Parse command
case "$1" in
	setenv )
		shift
		if [ $# -lt 2 ]; then
			help
			exit 1
		fi
		echo "setenv $1 $2" >> $FIFO
		;;
	print )
		shift
		if [ $# -eq 0 ]; then
			echo "print" >> $FIFO
		else
			echo "print $@" >> $FIFO
		fi
		;;
	* )
		break
		;;
esac
