#!/bin/bash

LISTA=""
TLISTA=""
rm -rf *.o

if [ -f ./libmocap.a ]; then 
    echo "[+] Maya library found."
else 
    GDZIE=`pwd`
    echo "[!] Copy libmocap.a to $GDZIE first!"
fi
for i in `ls *.c`; do
    echo "[*] $i"
    nazwa=`basename $i .c`
    gcc -g -c $i -o $nazwa.o `pkg-config opencv --cflags --libs`
    TLISTA=`echo $LISTA $nazwa.o`
    LISTA=$TLISTA
done
echo ":[ $LISTA ]:"
gcc -g $LISTA -lm -o test `pkg-config opencv --cflags --libs` -lmocap -L.
if [ -f ./test ]; then 
    echo "[+] Done."
else 
    echo "[!] Failed."
fi
