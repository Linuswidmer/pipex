/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:10:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 11:34:07 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
Child process that is executed first.
Duplicates the file descriptor for STDOUT into the write end of the pipe. 
*/
void	child_write_pipe(t_data *data, int *pipefd, t_cmd *cmd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	execve(cmd->path, cmd->args, NULL);
	close(pipefd[1]);
	terminate_on_error(data, NULL, "execve");
}

/*
Child process that is executed second.
Uses the read end of the pipe for STDIN and writes its output to the file 
pointed to by cmd->fd.
*/
void	child_read_pipe_write_file(t_data *data, int *pipefd, t_cmd *cmd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(cmd->fd, STDOUT_FILENO);
	execve(cmd->path, cmd->args, NULL);
	close(pipefd[0]);
	terminate_on_error(data, NULL, "execve");
}

/*
Checks if the number of arguments provided is 5.
Checks if the input file for the first command is readable'
*/
void	check_input(int argc, char **argv)
{
	if (argc != 5)
		terminate_on_error(NULL, NULL, "Invalid number of arguments");
	if (access(argv[1], R_OK) != 0)
		terminate_on_error(NULL, NULL, "Infile");
}

int	main(int argc, char *argv[])
{
	pid_t	pid1;
	pid_t	pid2;
	t_data	*data;

	check_input(argc, argv);
	data = init(argc, argv);
	if (!create_pipe(data))
		terminate_on_error(data, NULL, "pipe");
	if (!create_fork(&pid1))
		terminate_on_error(data, NULL, "fork");
	if (pid1 == 0)
		child_write_pipe(data, data->pipefd, data->arr_cmds[0]);
	if (!create_fork(&pid2))
		terminate_on_error(data, NULL, "fork");
	if (pid2 == 0)
		child_read_pipe_write_file(data, data->pipefd, data->arr_cmds[1]);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	terminate_on_success(data);
	return (0);
}
