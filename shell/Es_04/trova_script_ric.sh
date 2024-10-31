#!/bin/sh

cd $1

for i in *.sh
do
    if [ `grep -c $i "#!/bin/bash"` -gt 0 ]
    then
        $i >> "$PATH/script.txt"
    fi
    if [ `grep -c $i "#!/bin/bash"` -gt `cat "/tmp/Max.tmp"` ]
    then
        $i > "/tmp/Nome.tmp"
        `grep -c $i "#!/bin/bash"` > "/tmp/Max.tmp"
    fi
done

for d in *
do 
    if [ -d $d -a -r $d ]
    then 
        trova_script_ric $1
    fi
done