#!/bin/sh

cd $1

for i in *.sh
do 
    if [ $(grep -c "#!/bin/sh" $i) -gt 0 ]; then
        if [ $(grep -c "#!/bin/sh" $i) -gt $(cat "/tmp/Max.tmp") ];then
            echo $(grep -c "#!/bin/sh" $i) > "/tmp/Max.tmp"
            echo $i > "/tmp/NomeMax.tmp"
        fi
        echo $i >> "/tmp/Script.txt"
    fi
done

for d in *
 do
     if [ -d $d ] && [ -x $d ];then
         sh ripeti_ric.sh $d
     fi
 done
