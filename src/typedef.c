/*
 * syntelos type definition tool
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include <stddef.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uintptr_t word_t;

typedef uint8_t bool_t;

#define true 1
#define false 0

#define null 0

typedef unsigned char char_t;

typedef void* ptr_t;

typedef void* object_t;

typedef int fd_t;

#define device_mmap_prot (PROT_READ|PROT_WRITE)

static const char_t *usage_text[] = {
  "Synopsis",
  "",
  "  typedef <inc/source.h>",
  "",
  "Description",
  "",
  "  Enumerate typedefs from source.",
  "",
  "Synopsis",
  "",
  "  typedef <inc/source.h> <symbol>",
  "",
  "Description",
  "",
  "  Lookup type <symbol> from source.",
  "",
  "Synopsis",
  "",
  "  typedef ?",
  "",
  "Description",
  "",
  "  This message.",
  ""
};
static const size_t usage_text_len = 16;
/*
 * CLI synopsis.
 */
int usage(){
  size_t ix = 0;
  for (; ix < usage_text_len; ix++){
  
    fprintf(stderr,"%s\n",usage_text[ix]);
  }
  return 0;
}

#define string_size 0x100

typedef struct {
  char_t object[string_size];
  size_t length;

} string_t;

bool_t string_copy(string_t *tgt, const char_t *src, size_t len){
  memset(tgt,0,sizeof(string_t));
  if (null != src && 0 != len){
    memcpy(tgt->object,src,len);
    tgt->length = len;
    return true;
  }
  else {
    return false;
  }
}

typedef struct {
  string_t file;
  size_t size;
  object_t object;
  off_t offset;
} device_t;

bool_t device_open(device_t *device, char_t *src){
  memset(device,0,sizeof(device_t));

  fd_t fd = open(src,(O_CREAT|O_RDWR),0644);
  if (-1 < fd){

    struct stat st;
    if (0 == fstat(fd,&st) && S_IFREG == (st.st_mode & S_IFREG)){

      size_t size = st.st_size;
      if (0 < size){

	string_copy(&(device->file),src,strlen(src));

	device->size = size;

	device->object = mmap(null,size,device_mmap_prot,MAP_SHARED,fd,0);

	close(fd);

	return true;
      }
      else {
	close(fd);
      }
    }
    else {
      close(fd);
    }
  }
  return false;
}

void device_close(device_t *device){

    munmap(device->object,device->size);
}

#define symbol_size 0x20

typedef struct {
  char_t object[symbol_size];
  size_t length;

} symbol_t;

#define code_size 0x1000

typedef struct {
  char_t object[code_size];
  size_t length;

} code_t;

typedef struct {
  code_t code;
  symbol_t symbol;

} typedef_t;

bool_t typedef_copy(typedef_t *tgt, const char_t *begin, const char_t *end){
  memset(tgt,0,sizeof(typedef_t));

  ssize_t count = (end-begin);
  if (0 < count){
    {
      memcpy(tgt->code.object,begin,count);
      tgt->code.length = count;
    }
    {
      begin = tgt->code.object;
      end = (begin+count);

      char_t *sp = (char_t*)(end-1);
      if (';' == *sp){
	end = sp; sp--;

	if (')' == *sp){      // (function pointer)

	  begin += 8;
	}
	else {
	  while (' ' != *sp){ // (generic)
	    begin = sp--;
	  }
	}

	count = (end-begin);
	if (0 < count){

	  memcpy(tgt->symbol.object,begin,count);

	  tgt->symbol.length = count;

	  return true;
	}
      }
    }
  }
  return false;
}

bool_t typedef_next(typedef_t *target, device_t* device){

  char_t *device_origin = device->object;
  char_t *device_begin = (device_origin+device->offset);
  char_t *device_end = (device_origin+device->size);
  char_t *offset = device_begin;

  for (; device->offset < device->size; device->offset++){

    if ('\n' == *offset++){

      char_t *mem_begin = offset;      
      if (0 == strncmp("typedef ",mem_begin,8)){

	ssize_t mem_count = (device_end-mem_begin);
	if (0 < mem_count){

	  char_t *mem_end = memchr(mem_begin,'\n',mem_count);
	  if (null != mem_end){

	    if ('{' == *(mem_end-1)){

	      mem_count = (device_end-mem_begin);
	      if (0 < mem_count){

		mem_end = memchr(mem_end,'}',mem_count);
		if (null != mem_end){

		  mem_count = (device_end-mem_end);
		  if (0 < mem_count){

		    mem_end = memchr(mem_end,';',mem_count);
		    if (null != mem_end){

		      mem_count = (device_end-mem_end);
		      if (0 < mem_count){

			mem_end = memchr(mem_end,'\n',mem_count);
		      }
		    }
		  }
		}
	      }
	    }

	    if (device_begin < mem_begin && mem_begin < mem_end && mem_end <= device_end){

	      device->offset = (mem_end-device_origin);

	      return typedef_copy(target,mem_begin,mem_end);
	    }
	  }
	}
      }
    }
  }
  return false;
}

int main(int argc, char **argv){
  int argx = 1;
  if (argx < argc){
    device_t device, *dp = &device;
    if (device_open(&device,argv[argx])){
      argx += 1;
      if (argx < argc){
	char_t *query = argv[argx];
	typedef_t target, *tp = &target;
	while (typedef_next(tp,dp)){
	  if (0 == strcmp(target.symbol.object,query)){

	    fprintf(stdout,"%s\n",target.code.object);
	  }
	}
      }
      else {
	typedef_t target, *tp = &target;
	while (typedef_next(tp,dp)){

	  fprintf(stdout,"%s\n",target.code.object);
	}
      }
      device_close(dp);
      return 0;
    }
    else {
      return usage();
    }
  }
  else {
    return usage();
  }
}
