#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#define syntelos_mark 0x73796e74656c6f73
#define fdin 0
#define fdout 1
#define fderr 2

typedef uint64_t mark_t;
typedef void* ptr_t;

mark_t decompose(char *arg){
  size_t len = strlen(arg);
  mark_t src = syntelos_mark;
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
    mark_t src = decompose(operand);
    mark_t tgt = (src^syntelos_mark);

    argx += 1;
    if (argx < argc){
      char *operator = argv[argx];
      if (0 == strcmp(operator,"bin")){

	write(fdout,&tgt,8);
      }
      else {
	fprintf(stdout,"0x%zX\n",tgt);
	return 0;
      }
      
    }
    else {
      fprintf(stdout,"0x%zX\n",tgt);
      return 0;
    }
  }
  else {
    fprintf(stderr,"usage: %s <keyword> [hex|bin]\n",argv[0]);
    return 1;
  }
}
