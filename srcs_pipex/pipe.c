/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:10:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/17 18:03:07 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void first_child_process(int *pipefd, char **args_cmd)
{
	char *path;

    close(pipefd[0]);
	path = ft_strjoin("/bin/", args_cmd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    execve(path, args_cmd, NULL);
    perror("execve");
    exit(EXIT_FAILURE);
}

void second_child_process(int *pipefd, char **args_cmd, char *outfile)
{
  int fd;
char *path;

	path = ft_strjoin("/bin/", args_cmd[0]);
  close(pipefd[1]); 
  dup2(pipefd[0], STDIN_FILENO); 
  fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  if (fd == -1) 
  {
    perror("open");
    exit(EXIT_FAILURE);
  }
  dup2(fd, STDOUT_FILENO);
  execve(path, args_cmd, NULL);
  perror("execve");
  exit(EXIT_FAILURE);

}

char **process_input(char *input, char *file)
{
	char **cmd;
	char **args;
	int num_args;

	num_args = 0;
	cmd = ft_split(input, ' ');
	while (cmd[num_args])
		num_args++;
	if (file)
		num_args++;
	args = malloc(sizeof(char *) * (num_args + 1));
	args[0] = cmd[0];
	args[1] = cmd[1];
	if (file)
	{
		args[2] = file;
		args[3] = NULL;
	}
	else
		args[2] = NULL;
	return (args); 
}

pid_t create_fork()
{
	pid_t pid;

	pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
	return (pid); 
	
}

void create_pipe(t_data *data)
{
    if (pipe(data->pipefd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[]) {
    pid_t pid1;
	pid_t pid2;
    char **args_cmd[2];
	char **cmd1;
	char **cmd2;
	t_data *data;

	data = malloc(sizeof(t_data));
	args_cmd[0] = process_input(argv[2], argv[1]);
    args_cmd[1] = process_input(argv[3], NULL);
    create_pipe(data);
	
	pid1 = create_fork();
	if (pid1 ==0)
      first_child_process(data->pipefd, args_cmd[0]);
    pid2 = create_fork();
    if (pid2 == 0)
      second_child_process(data->pipefd, args_cmd[1], argv[4]);

    close(data->pipefd[0]);
    close(data->pipefd[1]);
    waitpid(pid1, NULL, 0); 
    waitpid(pid2, NULL, 0);

    free(args_cmd[1]);
	free(args_cmd[0][0]);
	free(args_cmd[0][1]);
	//free(args_cmd[0][2]);
	//free(args_cmd[0][3]);
	free(args_cmd[0]);
	free(data);

    return 0;
}

