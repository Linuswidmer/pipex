#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd[2];
    char buffer[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // after the fork command everyting is executed by the parent and the child seperately
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // Child process: read from the pipe
        close(fd[1]); // Close the write end of the pipe
        read(fd[0], buffer, sizeof(buffer));
        printf("Child process received message: %s\n", buffer);
        close(fd[0]); // Close the read end of the pipe
        return 0;
    }
    else {
        // Parent process: write to the pipe
        close(fd[0]); // Close the read end of the pipe
        char *message = "Hello from parent process!";
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]); // Close the write end of the pipe
        return 0;
    }
}

