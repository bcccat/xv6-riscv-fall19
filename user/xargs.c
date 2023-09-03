#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"


// Be vary careful about the exec function, its second parameter argv is in the form: 
// [[command], [arg1], [arg2], ...]
// thus, for xargs, we only need to change arg2 part in the simplified scenario 

int
main(int argc, char *argv[]){
    int index = 1;
    int _argc = 1;
    char *_argv[MAXARG];

     _argv[0] = malloc(strlen(argv[index])+1);
    strcpy(_argv[0],argv[index]);
    for(int i=index+1;i<argc;++i){
        _argv[_argc] = malloc(strlen(argv[i])+1);
        strcpy(_argv[_argc++],argv[i]);
    }
    _argv[_argc] = malloc(128);

    char buf;
    int i =0;
    while(read(0,&buf,1)){
        if(buf=='\n'){
            _argv[_argc][i++]='\0';
            if(fork()==0){
                exec(argv[index],_argv);
            }else{
                i=0;
                wait(0);
            }
        }else{
            _argv[_argc][i++]=buf;
        }
    }
    exit(0);
}