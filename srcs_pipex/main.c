#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int main(int argc, char **argv)
{
  int fd[2];
  char **args_cmd2;
  char **args_cmd1;
  pid_t pid;
  int status;
  int fd_outfile;
  char buffer[100];
  int bytes_read;
  char *const cmd1[] = {"grep", "a"};
  char *const cmd2[] = {"wc", "-w"};
  //char *const args[] = {"wc", "-l", "infile", NULL};
  char *const envp[] = {NULL};
  
  args_cmd1 = malloc(sizeof(char *) * 4);
  args_cmd1[0] = cmd1[0];
  args_cmd1[1] = cmd1[1];
  args_cmd1[2] = argv[1];
  args_cmd1[3] = NULL;
  

  pipe(fd); // creates a reading fd[0] and a writing fd[1] for processes to communicate
  pid = fork();
  if (pid == -1)
  {
      perror("fork");
      return 1;
  }
  else if (pid == 0)
  {
    close(fd[0]); // Close the read end of the pipe
    dup2(fd[1], STDOUT_FILENO); //replaces the fd for tsdout with our fd[1]
    execve("/bin/grep", args_cmd1, envp);
    close(fd[1]); // Close the write end of the pipe
    return 0;

  }
  else
  {
    waitpid(pid, &status, 0); // waits till status is 0
    bytes_read = read(fd[0], buffer, sizeof(buffer));
    args_cmd2 = malloc(sizeof(char *) * 4);
    args_cmd2[0] = cmd2[0];
    args_cmd2[1] = cmd2[1];
    args_cmd2[2] = ft_substr(buffer, 0, bytes_read + 1);
    args_cmd2[3] = NULL;
    fd_outfile = open("outfile", O_WRONLY);
    dup2(fd[0], STDIN_FILENO); //redirects the output from stdout to the outfile
    // printf("%s %s %s", args_cmd2[0], args_cmd2[1], args_cmd2[2]);
    // printf("%s\n", args_cmd2[2]);
    // execve("/bin/wc", args_cmd2, envp);
    // fd[1] = open(argv[2], O_WRONLY);
    // write(fd[1], buffer, bytes_read);
    close(fd[0]); // Close the read end of the pipe
    close(fd[1]); // Close the write end of the pipe
    return 0;

  }
}
