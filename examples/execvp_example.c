#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  char **args;
  char *const argv[] = {"ls", "-l", NULL};
  char *const envp[] = {NULL};
  execve("/bin/ls", argv, envp);
  perror("execvp");
}
