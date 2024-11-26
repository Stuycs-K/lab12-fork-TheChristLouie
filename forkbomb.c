#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
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
        return *x;
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
            return *y;
        }
        else{
          int status=0;
          pid_t r;
          r = wait(&status);
          printf("Main Process %d is done. Child %d slept for %d seconds\n", getpid(), r, WEXITSTATUS(status));
        }
    }
}

int* random_number_generator(int max){
    int r_file = open("/dev/random", O_RDONLY , 0);
    if(r_file == -1){
        err();
    }
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

/*
void loopforever(){
    int i = 0;
    while (i==0){
        printf("PID is : %d\n", getpid());
        signal(SIGINT, sighandler);
        signal(SIGQUIT, sighandler);
        sleep(1);
    }
}

static void sighandler( int signo ){
    if ( signo == SIGINT){
        char buffer[100] = "";
        sprintf(buffer, "Process with PID: %d Exiting due to SIGINT\n", getpid());
        printf(buffer);
        int w_file = open("output.txt", O_WRONLY | O_APPEND | O_CREAT, 0611);
        write(w_file, buffer, sizeof(buffer));
        close(w_file);
        exit(0);
    }
    else if ( signo == SIGQUIT){
        printf("PPID: %d , PID: %d\n", getppid(), getpid());
    }
}
*/
