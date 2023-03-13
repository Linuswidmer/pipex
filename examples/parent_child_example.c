#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  int status;

  // the fork command created a child process, that is assigned an id (pid)
  pid = fork();
  //printf("%i\n", pid);
  if (pid == -1) {
        // Failed to create a child process
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Hello from child process!\n");
        return 0;
    }
    else {
        // Parent process
        waitpid(pid, &status, 0);
        printf("Hello from parent process! Child process ID is %d\n", pid);
        return 0;
    }
}
