#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int fd;
  char **args;
  char buf[100];
  char *const cmd[] = {"wc", "-l"};
  //char *const args[] = {"wc", "-l", "infile", NULL};
  char *const envp[] = {NULL};

  fd = open(argv[1], O_RDONLY);
  read(fd, &buf, 100);
  args = malloc(sizeof(char *) * 4);
  args[0] = cmd[0];
  args[1] = cmd[1];
  args[2] = argv[1];
  args[3] = NULL;

  execve("/bin/wc", args, envp);

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
