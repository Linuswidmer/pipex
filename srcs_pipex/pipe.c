#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

char **args_creator(char **cmd, char *file)
{
  char **args;

  args = malloc(sizeof(char *) * 4);
  args[0] = cmd[0];
  args[1] = cmd[1];
  args[2] = file;
  args[3] = NULL;
  return (args); 
}

void first_child_process(int *pipefd, char **args_cmd)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    execve("/bin/grep", args_cmd, NULL);
    perror("execve");
    exit(EXIT_FAILURE);
}

void second_child_process(int *pipefd, char **args_cmd)
{
  int fd;

  close(pipefd[1]); 
  dup2(pipefd[0], STDIN_FILENO); 
  fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  if (fd == -1) 
  {
    perror("open");
    exit(EXIT_FAILURE);
  }
  dup2(fd, STDOUT_FILENO);
  execve("/bin/wc", args_cmd, NULL);
  perror("execve");
  exit(EXIT_FAILURE);

}

int main(int argc, char *argv[]) {
    int pipefd[2];
    int pipe_return;
    pid_t pid1, pid2;
    char **args_cmd[2];
    char *cmd1[] = {"grep", "a"};
    char *cmd2[] = {"wc", "-w"};

    args_cmd[0] = args_creator(cmd1, argv[1]);
    args_cmd[1] = args_creator(cmd2, NULL);
    pipe_return = pipe(pipefd);
    if (pipe_return == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid1 = fork();
    if (pid1 == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid1 == 0) 
      first_child_process(pipefd, args_cmd[0]);

    pid2 = fork();
    if (pid2 == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid2 == 0)
      second_child_process(pipefd, args_cmd[1]);

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0); // Wait for first child process to finish
    waitpid(pid2, NULL, 0); // Wait for second child process to finish
    free(args_cmd[0]);
    free(args_cmd[1]);

    return 0;
}

