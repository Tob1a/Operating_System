#bin/sh

cd $1

#cerco i file che contengono la parola $2

for i in *
do
    if [ -f "$i" -a -r "$i" ]
    then

        #controllo il numero dei messaggi
        if [ $(grep -c "$2" $i) -gt 0 ]
        then
            echo "$(grep -c $2 $i), $i" >> "`pwd`/trovati.txt"
        fi
        #controllo il massimo nel singolo file
        
        if [ $(grep -c $2 $i) -gt `cat /tmp/Maxcounter.tmp` ]
        then 
            echo "$(grep -c $2 $i)" > "/tmp/Maxcounter.tmp"
            
        fi
    fi
done 

#inizio a eseguire lo script ricorsivamente

for d in *
do
    if [ -d $d -a -x $d ]
    then 
        identifica_ric.sh $d $2
    fi
done

