#!/bin/sh

if [ $# -lt 2 ]
then 
    echo "Hai inserito meno di 2 argomenti";
    exit 1;
fi

case $1 in 
    *) echo "Non e' una path assoluta";
        exit 1;;
    /*);;
esac

export PATH=$PATH:`pwd`

0 > "/tmp/Max.tmp"
> "/tmp/Nome.tmp"

if [ -f "script.txt" -a -r "script.txt" ]
then
    > "script.txt"
fi

trova_script_ric.sh $1

rm -f "/tmp/Max.tmp"
rm -f "/tmp/Nome.tmp"