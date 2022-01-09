for src in $(2>/dev/null ls dot.* | egrep -v '^dot.sh$')
do
    tgt=~/$(echo ${src} | sed 's%^dot%%');
    if cp -p ${src} ${tgt}
    then
        ls -l ${tgt}
    else
        cat<<EOF>&2
$0: error in 'cp -p ${src} ${tgt}' 
EOF
    fi
done
