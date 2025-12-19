#!/bin/sh
SCRIPT=./run.sh
TESTENV_DIR=./testenv

echo "Removing old links in $TESTENV_DIR"
rm -rf $TESTENV_DIR >/dev/null 2>&1

echo "Creating new links in $TESTENV_DIR"
mkdir $TESTENV_DIR
cd $TESTENV_DIR

EXE=../bin/test
if [ ! -e $EXE ]; then
	echo "Warning: '$EXE' does not exist." >&2
else
	ln -sf $EXE .
fi

VXT_LIB_DIR=../../dist/lib
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
