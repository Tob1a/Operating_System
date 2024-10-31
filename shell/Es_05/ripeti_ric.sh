#!/bin/sh

cd $1

for i in *
do
    if [ $(grep -c $2 $i) -gt 0 ]
    then
        if [ "$(grep -c $2 $i)" -gt "$(cat /tmp/Maxnum.tmp)" ]
        then
            "$(grep -c $2 $i)" > "/tmp/Maxnum.tmp"
            "$(pwd)/$i" > "$1/Max.tmp"
        fi
        "$(grep -c $2 $i) $i" >> "$1/Trovati.tmp"
    fi
done

for d in *
do
    if [ -d $d -a -x $d ]; then
    sh ripeti_ric.sh $d $2
    fi
done
