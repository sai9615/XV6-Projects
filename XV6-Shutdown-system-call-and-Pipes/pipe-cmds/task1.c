#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
FILE *fp;
char *mode = "r";
char text[100], word[100] = ""; 
char *commands[100];
int i=0;
int pid, pipe1[2], pipe2[2];
int wait_pid;


fp = fopen("cmds", mode);

if (fp == NULL) {
  fprintf(stderr, "Can't open cmds file!\n");
  exit(1);
}
else {
	printf("cmds file has been opened and is being parsed.....\n");
	while(fscanf(fp, "%s", text) != EOF )
	{
		strcat(word, text);
		strcat(word, "\n");
	}
}


for(char *toks = strtok(word, "\n"); toks != NULL; toks = strtok(NULL, "\n"))
{
	commands[i] = malloc(strlen(toks) + 1);
	strcpy(commands[i], toks);
	i++;
}
    
// now creating two pipes.
pipe(pipe1);
pipe(pipe2);

printf("In parent (pid = %d) \n", (int) getpid());
 pid = fork();
 if(pid == 0){
 	printf("In child-1 (pid = %d),:executing command %s \n", (int) getpid(), commands[0]);
 	dup2(pipe1[1], 1);
 	close(pipe1[0]);
 	close(pipe1[1]);
 	close(pipe2[0]);
 	close(pipe2[1]);
 	execlp(commands[0], commands[0], commands[1], NULL);
 }
 else {
 	pid = fork();
 	if(pid == 0){
 	printf("In child-2 (pid = %d),:executing command %s \n", (int) getpid(), commands[2]);
 	dup2(pipe1[0], 0);
 	dup2(pipe2[1], 1);
 	close(pipe1[0]);
 	close(pipe1[1]);
 	close(pipe2[0]);
 	close(pipe2[1]);
 	execlp(commands[2], commands[2], commands[3], NULL);
 	}
else {
	pid = fork();
	if(pid == 0){
  	printf("In child-3 (pid = %d),:executing command %s \n", (int) getpid(), commands[4]);
 	dup2(pipe2[0], 0);
 	close(pipe1[0]);
 	close(pipe1[1]);
 	close(pipe2[0]);
 	close(pipe2[1]);
 	execlp(commands[4], commands[4], commands[5], NULL);
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

fclose(fp);
    return 0;
}



