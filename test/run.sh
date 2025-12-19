#!/bin/sh
EXE=./testenv/test
FIFO=/tmp/fifo
VXT_LIB_DIR=./testenv
VXT_ASSETS_DIR=./testenv/assets
LD_LIBRARY_PATH=$VXT_LIB_DIR:$LD_LIBRARY_PATH
LOGFILE=./test.log

if [ ! -x $VXT_LIB_DIR/libvxt.so ]; then
	echo "Shared object '$VXT_LIB_DIR/libvxt.so' does not exist or does not have execute permissions." >&2
	exit 1
fi

if [ ! -x $EXE ]; then
	echo "Executable file '$EXE' does not exist or does not have execute permissions." >&2
	exit 1
fi

if [ -p $FIFO ]; then
	rm -f $FIFO
fi

mkfifo $FIFO

# Attach the fifo to a file descriptor.
# Which causes the shell to buffer data written to the fifo.
# Without it, any write to the fifo blocks until something reads what is written.
exec 3<> $FIFO

ulimit -c -S unlimited

export LD_LIBRARY_PATH VXT_ASSETS_DIR
$EXE < $FIFO
