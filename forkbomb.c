#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "forkbomb.h"

void process(){
    pid_t p;
    p = fork();
    if(p<0){
        perror("fork fail");//output to stderr instead of stdout
        exit(1);
    } else if ( p == 0){
        int* x = random_number_generator(5);
        printf("%d %dsec\n", getpid(),*x);
        sleep(*x);
        printf("%d finished after %dsec\n", getpid(), *x);
        exit(*x);
    }else{
        printf("%d about to create %d child processes\n", getpid(),2);
        pid_t q;
        q=fork();
        if(q<0){
            perror("fork fail");//output to stderr instead of stdout
            exit(1);
        } else if ( q == 0){
            int* y = random_number_generator(5);
            printf("%d %dsec\n", getpid(),*y);
            sleep(*y);
            printf("%d finished after %dsec\n", getpid(), *y);
            exit(*y);
        }
        else{
          int status=0;
          pid_t r;
          r = wait(&status);
          printf("Main Process %d is done. Child %d slept for %dsec\n", getpid(), r, WEXITSTATUS(status));
        }
    }
}

int* random_number_generator(int max){
    int r_file = open("/dev/random", O_RDONLY , 0);
    int* x = malloc(sizeof(int));
    read(r_file, x, sizeof(int));
    close(r_file);
    (*x) = (*x) % max;
    if (*x < 0){
      *x=(*x)*-1;
    }
    (*x)++;
    return x;
}