#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  int fd[2];
  char **args;
  pid_t pid;
  int status;
  char buffer[100];
  char *const cmd[] = {"wc", "-l"};
  //char *const args[] = {"wc", "-l", "infile", NULL};
  char *const envp[] = {NULL};

  pipe(fd);
  pid = fork();
  if (pid == -1)
  {
      perror("fork");
      return 1;
  }
  else if (pid == 0)
  {
    fd[0] = open(argv[1], O_RDONLY);
    read(fd[0], &buffer, 100);
    write(fd[1], buffer, strlen(buffer) + 1);
    close(fd[1]); // Close the write end of the pipe
    close(fd[0]); // Close the read end of the pipe
    return 0;

  }
  else
  {
    printf("Status is %i\n", status); //what does the status mean
    waitpid(pid, &status, 0);
    read(fd[0], buffer, sizeof(buffer));
    fd[1] = open(argv[2], O_WRONLY);
    write(fd[1], buffer, sizeof(buffer));
    close(fd[0]); // Close the read end of the pipe
    close(fd[1]); // Close the write end of the pipe
    return 0;

  }

  // fd[0] = open(argv[1], O_RDONLY);
  // read(fd[0], &buf, 100);
  // args = malloc(sizeof(char *) * 4);
  // args[0] = cmd[0];
  // args[1] = cmd[1];
  // args[2] = argv[1];
  // args[3] = NULL;

  // execve("/bin/wc", args, envp);

  // int fd_file1;
  // int fd_file2;
  //
  // fd_file1 = open(argv[1], O_RDONLY);
  // printf("%i\n", fd_file1);
  // fd_file2 = open(argv[3], O_RDONLY);
  // printf("%i\n", fd_file2);
  // if (fd_file1 == -1 || fd_file2 == -1) 
  //   perror("Error opening file");
}
