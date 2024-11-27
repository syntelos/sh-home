
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi
fi


SH_HOME=${HOME}/src/syntelos/sh-home/bin
if [ -d "${SH_HOME}" ] ; then
    PATH="${SH_HOME}:$PATH"
fi

BIN_HOME=${HOME}/bin
if [ -d "${BIN_HOME}" ] ; then
    PATH="${BIN_HOME}:$PATH"
fi

SHTEX=${HOME}/tex/sh-tex
if [ -d ${SHTEX} ]
then
	PATH="${PATH}:${SHTEX}"
fi

export GOPATH=${HOME}/go
export GOBIN=${GOPATH}/bin

if [ -d "${GOBIN}" ] ; then
    PATH="${PATH}:${GOBIN}"
fi

export GOROOT=/usr/local/go

if [ -d ${GOROOT} ]
then
	PATH="${PATH}:${GOROOT}/bin"
fi
