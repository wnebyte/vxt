#!/bin/sh
VERSION=0.1
PROGNAME="$(basename -- $0)"
OPTIONS=$(getopt -o "lwhv" --long "help,version" -n "$PROGNAME" -- "$@")
if [ $? -ne 0 ]; then exit 1; fi
eval set -- "$OPTIONS"

LINUX=1
WINDOWS=0

SCRIPT=./run.sh
TESTENV_DIR=./testenv
INSTALL_DIR=/mnt/c/Users/ralle/Tmp/vxt

# Parse options
while true; do
	case "$1" in
		-l )
			LINUX=1
			shift
			;;
		-w )
			WINDOWS=1
			shift
			;;
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

if [ $WINDOWS -ne 0 ]; then
	cp ./bin/Windows/$(uname -m)/test.exe $INSTALL_DIR
	cp ./bin/Windows/$(uname -m)/run.bat $INSTALL_DIR
	exit 0
fi

echo "Removing old links in $TESTENV_DIR"
rm -rf $TESTENV_DIR >/dev/null 2>&1

echo "Creating new links in $TESTENV_DIR"
mkdir $TESTENV_DIR
cd $TESTENV_DIR

EXE=../bin/Linux/$(uname -m)/test
if [ ! -e $EXE ]; then
	echo "Warning: '$EXE' does not exist." >&2
else
	ln -sf $EXE .
fi

VXT_LIB_DIR=../../dist/lib/Linux/$(uname -m)
if [ ! -e $VXT_LIB_DIR ]; then
	echo "Warning: '$VXT_LIB_DIR' does not exist." >&2
else
	ln -sf $VXT_LIB_DIR/*.so* .
fi

VXT_ASSETS_DIR=../../impl/assets
if [ ! -e $VXT_ASSETS_DIR ]; then
	echo "Warning: '$VXT_ASSETS_DIR' does not exist." >&2
else
	ln -sf $VXT_ASSETS_DIR .
fi

echo ""
echo "Start the application with $SCRIPT"
