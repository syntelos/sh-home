/*
 * syntelos host endian tool
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "endian.h"

int main(int argc, char **argv){

  if (endian_kind_le == endian()){

    printf("-D_ENDIAN_KIND=_ENDIAN_KIND_LE\n");
  }
  else {

    printf("-D_ENDIAN_KIND=_ENDIAN_KIND_BE\n");
  }
  return 0;
}
