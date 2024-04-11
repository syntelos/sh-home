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

mark_t decompose(char *arg){
  size_t len = strlen(arg);
  mark_t src = syntelos_mark();
  mark_t tgt = 0;
  char *sp = arg;
  char* tp = (char*)&tgt;
  char* zp = (char*)&src;
  off_t idx;
  for (idx = 0; idx < 8; idx++, tp++){
    if (idx >= len){
      *tp = *zp++;
    }
    else {
      *tp = *sp++;
    }
  }
  return tgt;
}

int main(int argc, char **argv){
  int argx = 1;
  if (argx < argc){
    char *operand = argv[argx];
    if (0 == strcmp("syntelos",operand) || 0 == strcmp("device",operand)){
      mark_t src = syntelos_mark();
      argx += 1;
      if (argx < argc){
	char *operator = argv[argx];
	if (0 == strcmp(operator,"bin")){

	  write(fd_out,&src,8);
	}
	else {
	  fprintf(stdout,"0x%zX\n",src);
	  return 0;
	}
      
      }
      else {
	fprintf(stdout,"0x%zX\n",src);
	return 0;
      }
    }
    else {
      mark_t syn = syntelos_mark();
      mark_t src = decompose(operand);
      mark_t tgt = (src+syn);

      argx += 1;
      if (argx < argc){
	char *operator = argv[argx];
	if (0 == strcmp(operator,"bin")){

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
	fprintf(stdout,"0x%zX\n",tgt);
	return 0;
      }
    }
  }
  else {
    fprintf(stderr,"usage: %s <keyword> [hex|bin]\n",argv[0]);
    return 1;
  }
}
