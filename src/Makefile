CC := $(shell which clang)
#
# [XOPEN:600 POSIX:200112L] SUSv3 / UNIX 03 / POSIX.1-2001 / XPG6
# [XOPEN:700 POSIX:200809L] SUSv4 / UNIX 08 / POSIX.1-2008 / XPG7
#
PORT_CFL_PX := -D_XOPEN_SOURCE=700
PORT_CFL_PO := -D_POSIX_C_SOURCE=200809L
PORTABILITY := $(PORT_CFL_PX) $(PORT_CFL_PO)
#
# CONSISTENCY [ignore char sign]
#
WARNINGS := -Wno-pointer-sign
#
# REFLECTION
#
DEBUG := -g -ggdb
ENDIAN := $(shell endian)
#
# STRUCTURE
#
CCFLAGS := $(PORTABILITY) $(WARNINGS) $(DEBUG) -I. $(ENDIAN)

LDFLAGS := 

all: ~/bin/typedef ~/bin/mark ~/bin/endian

~/bin/typedef: typedef.c
	$(CC) $(CCFLAGS) -o $@ $< $(LDFLAGS) 

~/bin/mark: mark.c
	$(CC) $(CCFLAGS) -o $@ $< $(LDFLAGS) 

~/bin/endian: endian.c
	$(CC) $(CCFLAGS) -o $@ $< $(LDFLAGS) 

clean:
	$(RM) ~/bin/{typedef,mark,endian}

