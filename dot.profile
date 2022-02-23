
#umask 022

# if running bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi
fi

if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

export ANDROID_SDK=/opt/google/android_sdk
if [ -d ${ANDROID_SDK} ]
then
    PATH=${PATH}:${ANDROID_SDK}/tools/bin
fi

export JAVA_HOME=/usr/java
if [ -d ${JAVA_HOME} ]
then
    PATH=${PATH}:${JAVA_HOME}/bin
fi

export EMSDK=/home/jdp/src/emscripten-core/emsdk
if [ -d ${EMSDK} ]
then
    . ${EMSDK}/emsdk_env.sh
fi
