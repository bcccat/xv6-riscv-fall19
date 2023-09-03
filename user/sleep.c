#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    fprintf(2, "sleep: missing operand!\n");
    exit(1);
  }
  // printf("Input is %s\n", argv[1]);
  int sec = atoi(argv[1]);

  if(sec < 0){
    fprintf(2, "sleep: invalid operation %d!\n", sec);
    exit(1);
  }

  sleep(sec);
  exit(0);
}
