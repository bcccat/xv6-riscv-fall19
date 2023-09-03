#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
  if(argc != 1){
    fprintf(2, "pingpong: no input needed!\n");
    exit(1);
  }

  char buff[10];
  
  int p[2];

  pipe(p);
  int pid = fork();
  if(pid < 0){
     printf("error\n");
     exit(1);
  }

  if(pid == 0){
    read(p[0], buff, sizeof(buff));
    printf("%d: received %s\n", getpid(), buff);
    write(p[1], "pong", 5);

    close(p[0]);
    close(p[1]);
    exit(0);
  }else{
    write(p[1], "ping", 5);
    wait(0);
    read(p[0], buff, sizeof(buff));
    printf("%d: received %s\n", getpid(), buff);

    close(p[0]);
    close(p[1]);
  }
  exit(0);
}
