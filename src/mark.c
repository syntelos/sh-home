/*
 * syntelos type mark tool
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "endian.h"

#define fd_in 0
#define fd_out 1
#define fd_err 2

typedef uint8_t char_t;
typedef uint64_t mark_t;
typedef void* ptr_t;

mark_t syntelos_mark(){
  endian64_t mark ;
  memcpy(mark.data,"syntelos",8);
  return mark.value;
}

mark_t type_mark(char *arg){
  if (0 == strcmp("device",arg)){

    return syntelos_mark();
  }
  else {
    size_t len = strlen(arg);
    if (8 < len){
      mark_t re = 0;
      {
	char *src = arg;
	size_t cnt = len;
	endian64_t se;
	char *tgt = se.data;
	while (0 != cnt){
	  if (8 < cnt){
	    memcpy(tgt,src,8);
	    cnt -= 8;
	  }
	  else {
	    memset(tgt,0,8);
	    memcpy(tgt,src,cnt); // (N.B. Agnostic.)
	    cnt = 0;
	  }

	  if (0 == re)
	    re = se.value;
	  else
	    re += se.value;
	}
      }
      return re;
    }
    else {
      endian64_t mark ;
      memcpy(mark.data,arg,len);
      return mark.value;
    }
  }
}

int main(int argc, char **argv){
  int argx = 1;
  if (argx < argc){
    char *operand = argv[argx];
    mark_t syn = syntelos_mark();
    mark_t src = type_mark(operand);
    mark_t tgt = (syn*src); // maximal uniqueness as minimal collision rate

    argx += 1;
    if (argx < argc && 0 == strcmp(argv[argx],"bin")){

      if (syn == src){
	write(fd_out,&src,8);
      }
      else {
	write(fd_out,&tgt,8);
      }
    }
    else {
      if (syn == src){
	fprintf(stdout,"0x%zX\n",src);
      }
      else {
	fprintf(stdout,"0x%zX\n",tgt);
      }
      return 0;
    }
  }
  else {
    fprintf(stderr,"usage: %s <keyword> [hex|bin]\n",argv[0]);
    return 1;
  }
}
