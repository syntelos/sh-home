#!/bin/bash
#
function usage {
    cat<<EOF
Synopsis

  $0 (import|export)

Description

  Copy into version control with import.  Copy out of
  version control with export.

EOF
    exit 1
}
#
# Copy from version control source to version control target
#
function export {
    for base in $(2>/dev/null ls dot.* | egrep -v '^dot.sh$')
    do
        src=${base}
        tgt=~/$(echo ${base} | sed 's%^dot%%');
        if cp -p ${src} ${tgt}
        then
            ls -l ${tgt}
        else
            cat<<EOF>&2
$0: error in 'cp -p ${src} ${tgt}'
EOF
            return 1
        fi
    done
    return 0
}
#
# Copy from version control target to version control source
#
function import {
    for base in $(2>/dev/null ls dot.* | egrep -v '^dot.sh$')
    do
        src=~/$(echo ${base} | sed 's%^dot%%');
        tgt=${base}
        if cp -p ${src} ${tgt}
        then
            ls -l ${tgt}
        else
            cat<<EOF>&2
$0: error in 'cp -p ${src} ${tgt}'
EOF
            return 1
        fi
    done
    return 0
}
#
#
if [ -n "${1}" ]
then
    case "${1}" in
        import)
            if import
            then
                exit 0
            else
                exit 1
            fi
        ;;
        export)
            if export
            then
                exit 0
            else
                exit 1
            fi
            ;;
        *)
            usage
            ;;
    esac
else
    usage
fi
