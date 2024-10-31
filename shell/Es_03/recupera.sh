#!/bin/sh

if [ $# -lt 3 ]
then
    echo "hai inserito meno di 3 argomenti"
    exit 1
fi

case $1 in
    /*) echo " e' una directory assoluta" 
        exit 1;;
    *)
        case $2 in 
            /*) echo "e ' una direcotory assoluta"
                exit 1;;
            *);;
        esac
esac

export PATH=$PATH:`pwd`

#creazione dei file
if [ ! -d $2 ]
then
    mkdir $2
fi

> "/tmp/Maxhit.tmp"
echo 0 > "/tmp/Maxdir.tmp"
echo 0 > "/tmp/Totale.tmp"

recupera_ric.sh $1 $2 $3

echo "La directory e' : $(cat /tmp/Maxdir.tmp)"
echo "Il numero totale di file e' $(cat /tmp/Totale.tmp)"

rm -f /tmp/Maxhit.tmp
rm -f /tmp/Maxdir.tmp
rm -f /tmp/Totale.tmp


