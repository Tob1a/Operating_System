#!/bin/sh
if [ $# -gt 2 ];then
echo "Hai inserito piu di 2 argomenti"
exit 1
fi
case $1 in 
    /*) if [ ! -d $1 ];then
            echo "Non è una cartella";
            exit 1;
        fi;;
    *)  echo "Non e' una directory relativa"
        exit 1;;
esac

export PATH=$PATH:`pwd`

echo 0 > "/tmp/Max.tmp"
> "/tmp/NomeMax.tmp"

if [ ! -f "/tmp/Script.txt" ];then
    > "/tmp/Script.txt"
fi

sh ripeti_ric.sh $1

echo "Gli script massimi sono $(cat "/tmp/NomeMax.tmp") con $(cat "/tmp/Max.tmp")"

rm -f "/tmp/NomeMax.tmp"
rm -f "/tmp/Script.txt"
rm -f "/tmp/Max.tmp"