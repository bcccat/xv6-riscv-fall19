#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
    int min = 2;
    int p[2][2];
    int flag = 0;
    
    pipe(p[flag]);

    for(int i = 2; i <= 35; i++){
        write(p[flag][1], &i, sizeof(i));
    }
    close(p[flag][1]); // close after write finished

    while(fork() == 0){
        int item;
        if(read(p[flag][0], &min, sizeof(min)) != 0){
            printf("prime %d\n", min);
        }
        else{
            exit(0);
        }

        pipe(p[flag^1]);
        while(read(p[flag][0], &item, sizeof(item)) != 0){
            if(item%min != 0){
                write(p[flag^1][1], &item, sizeof(item));
            }
        }
        close(p[flag^1][1]); // close after write finished
        flag ^= 1;
    }

    close(p[1][0]);
    wait(0); // wait for children process
    exit(0);
}