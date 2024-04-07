#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  int argx = 1;
  if (argx < argc){
    printf("0x");
    char *arg = argv[argx];
    int len = strlen(arg);
    int idx;
    for (idx = 0; idx < len; idx++){
      printf("%02x",arg[idx]);
    }
    printf("\n");
    return 0;
  }
  else {
    return 1;
  }
}
