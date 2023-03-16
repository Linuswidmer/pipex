#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2;
    char **args_cmd1;
    char **args_cmd2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child process 1
        close(pipefd[0]); // Close unused read end of the pipe

        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe

        char *const cmd1[] = {"grep", "a"};
        args_cmd1 = malloc(sizeof(char *) * 4);
        args_cmd1[0] = cmd1[0];
        args_cmd1[1] = cmd1[1];
        args_cmd1[2] = argv[1];
        args_cmd1[3] = NULL;
        // char *cmd1[] = {"/bin/grep", "grep", "a", NULL};
        execve("/bin/grep", args_cmd1, NULL); // Execute first command
        perror("execve"); // Will only be reached if execve fails
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child process 2
        close(pipefd[1]); // Close unused write end of the pipe

        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to read end of pipe

        // char *cmd2[] = {"/bin/wc", "wc", "w", NULL};
        char *const cmd2[] = {"wc", "-w"};
        args_cmd2 = malloc(sizeof(char *) * 3);
        args_cmd2[0] = cmd2[0];
        args_cmd2[1] = cmd2[1];
        args_cmd2[2] = NULL;
        execve("/bin/wc", args_cmd2, NULL); // Execute second command
        perror("execve"); // Will only be reached if execve fails
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0); // Wait for first child process to finish
    waitpid(pid2, NULL, 0); // Wait for second child process to finish

    return 0;
}

