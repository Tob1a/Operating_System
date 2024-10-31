#!/bin/sh
if [ $# -lt 2 ]
then 
    echo "Ci sono meno di due argomenti come input";
    exit 1;
fi
if [ -d $1 ] && [ -a $1 ]
then
    case $1 in 
        /*) 
                echo "E' un percorso assoluto e non relativo";
                echo "ti voglio bene"
                echo "Anche io"
                exit 1;
            ;;
        *);;
    esac
else
    echo "Errore nell'apertura della cartella";
    exit 1;
fi

export PATH=$PATH:`pwd`


if [ "$1/Trovati.tmp" -f ]
then
    rm -f "$1/Trovati.tmp"
fi

if [ "$1/Max.tmp" -f ]
then 
    rm -f "$1/Max.tmp"
fi

> "$1/Trovati.tmp"
> "$1/Max.tmp"
0 > "/tmp/Maxnum.tmp"

sh ripeti_ric.sh $1 $2

echo "I primi 5 file con il numero maggiore di occorenze sono $(head -n 5 | sort -n -d test/Trovati.tmp)"

rm -f "/tmp/Maxnum.tmp"


