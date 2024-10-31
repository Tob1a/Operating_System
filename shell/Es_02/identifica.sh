#!bin/sh
if [ $# -lt 2 ] 
then
    echo "hai inserito meno di 2 argomenti";
    exit 1
fi

case $1 in
    /*) echo "Non e' una path relativa";
    exit 2;;
    *);;
esac

#aggiorno path
export PATH=$PATH:`pwd`

#clean file 
> "$1/trovati.txt"
> "$1/Max.txt"

echo 0 > "/tmp/Maxcounter.tmp"

#chiamo lo script ricorsivo
sh identifica_ric.sh $1 $2

echo "I cinque file che contengono il maggior numero di occorenze sono:"
echo `sort -r -n $1/trovati.txt | cut -f 2 -d ,`

rm -f /tmp/Maxcounter.tmp
