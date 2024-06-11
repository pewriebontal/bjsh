#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  char* cmd1[] = {"ls", "-l", NULL};
  char* cmd2[] = {"wc", "-l", NULL};
  char** cmds[] = {cmd1, cmd2, NULL};
  int pipefd[2];
  int pid;
  int pipd = dup(1);
  int status;
  int i = 0;
  int j = 0;

  while (cmds[i]){
    if (pipe(pipefd) == -1){
      perror("pipe");
      exit(1);
    }
    if ((pid = fork()) == -1){
      perror("fork");
      exit(1);
    }
    if (pid == 0){
      if (i != 0){
        dup2(pipefd[0], 0);
        close(pipefd[0]);
      }
      if (cmds[i + 1]){
        dup2(pipefd[1], 1);
        close(pipefd[1]);
      }
      printf("%s\n", cmds[i][0]);
      execvp(cmds[i][0], cmds[i]);
      perror("execvp");
      exit(1);
    } else {
      close(pipefd[0]);
      dup2(pipefd[1], 1);
      
    }
    close(pipefd[1]);
    i++;
  }
  while (waitpid(-1, &status, 0) != -1) {
    if (WIFEXITED(status)) {
      printf("child exited with status %d\n", WEXITSTATUS(status));
    } else {
      printf("child exited abnormally\n");
    }
  }
  printf("%s\n", cmds[0][0]);
  return 0;
}