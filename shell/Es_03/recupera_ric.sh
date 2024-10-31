#!/bin/sh

cd $1

for i in *.bak
do
    if [ -f $i -a -r $i ]
    then
    
        if [ `head -n 1 $i | grep -c $3` -gt 0 ]
        then
            cp $i "$PATH/recuperati"
        fi
    fi
done

for d in *
do
    if [ -d $d -a -x $d ]
    then
        recupera_ric $1 $2 $3
    fi
done