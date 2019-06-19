#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define print_usage(cmd) printf("Usage: %s 1|2|3\n", cmd)

int main(int argc, char * argv[]) 
{
    int option = 0;
    int pid, pipe1[2], pipe2[2];
    int wait_pid;
    pipe(pipe1);
    pipe(pipe2);
    char istr[] = "abc";

    setbuf(stdout, NULL);

    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    option = atoi(argv[1]);
    if (option != 1 && option != 2 && option != 3)
    {
        print_usage(argv[0]);
        return 1;        
    }
    else {
        switch(option){

        case 1: //printf("In parent (pid = %d) \n", (int) getpid());
                pid = fork();
                 if(pid == 0){
                    read(pipe1[0], istr, 20);
                    printf("Child-1 (pid = %d) is running \n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);

                 }
                 else {
                    pid = fork();
                    if(pid == 0){
                    read (pipe2[0], istr, 20);
                    write(pipe1[1],istr, strlen(istr) + 1);
                    printf("child-2 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);

                    }
                else {
                    pid = fork();
                    if(pid == 0){
                    write(pipe2[1],istr, strlen(istr) + 1);
                    printf("Child-3 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);
                    }
                  }
                }

                close(pipe1[0]);
                close(pipe1[1]);
                close(pipe2[0]);
                close(pipe2[1]);

                while ((wait_pid = wait(NULL)) > 0){
                    printf("In parent (pid = %d): successfully reaped child (pid: %d) \n",(int) getpid(), (int) wait_pid);
                }
                
                break;

        case 2: //printf("In parent (pid = %d) \n", (int) getpid());
                pid = fork();
                 if(pid == 0){
                    read(pipe1[0], istr, 20);
                    write(pipe2[1],istr, strlen(istr) + 1);
                    printf("Child-1 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);

                 }
                 else {
                    pid = fork();
                    if(pid == 0){
                    write(pipe1[1],istr, strlen(istr) + 1);
                    printf("Child-2 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);

                    }
                else {
                    pid = fork();
                    if(pid == 0){
                    read(pipe2[0],istr,20);
                    printf("Child-3 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);
                    }
                  }
                }

                close(pipe1[0]);
                close(pipe1[1]);
                close(pipe2[0]);
                close(pipe2[1]);

                while ((wait_pid = wait(NULL)) > 0){
                    printf("In parent (pid = %d): successfully reaped child (pid: %d) \n",(int) getpid(), (int) wait_pid);
                }
                
                break;

        case 3: // printf("In parent (pid = %d) \n", (int) getpid());
                pid = fork();
                 if(pid == 0){
                    read(pipe2[0], istr, 20);
                    write(pipe1[1],istr, strlen(istr) + 1);
                    printf("Child-1 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);

                 }
                 else {
                    pid = fork();
                    if(pid == 0){
                    read(pipe1[0],istr,20);
                    printf("Child-2 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);

                    }
                else {
                    pid = fork();
                    if(pid == 0){
                    write(pipe2[1],istr, strlen(istr) + 1);
                    printf("Child-3 (pid = %d) is running\n", (int) getpid());
                    close(pipe1[0]);
                    close(pipe1[1]);
                    close(pipe2[0]);
                    close(pipe2[1]);
                    }
                  }
                }

                close(pipe1[0]);
                close(pipe1[1]);
                close(pipe2[0]);
                close(pipe2[1]);

                while ((wait_pid = wait(NULL)) > 0){
                    printf("In parent (pid = %d): successfully reaped child (pid: %d) \n",(int) getpid(), (int) wait_pid);
                }
                
                break;
        }
    }

    return 0;
}
