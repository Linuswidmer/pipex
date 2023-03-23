/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:10:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/20 17:27:03 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_write_pipe(t_data *data, int *pipefd, t_cmd *cmd)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    execve(cmd->path, cmd->args, NULL);
    close(pipefd[1]);
    terminate_on_error(data, NULL, "execve");
}

void child_read_pipe_write_file(t_data *data, int *pipefd, t_cmd *cmd)
{
  close(pipefd[1]); 
  dup2(pipefd[0], STDIN_FILENO); 
  dup2(cmd->fd, STDOUT_FILENO);
  execve(cmd->path, cmd->args, NULL);
  close(pipefd[0]);
  exit(0);
  // terminate_on_error(data, NULL, "execve");
}

void check_input(int argc, char **argv)
{
  if (argc != 5)
    terminate_on_error(NULL, NULL, "Invalid number of arguments");
  if (access(argv[1], R_OK) != 0)
    terminate_on_error(NULL, NULL, "Infile");
}

int main(int argc, char *argv[]) 
{
  pid_t pid1;
	pid_t pid2;
	t_data *data;

  check_input(argc, argv);
	data = init(argc, argv);
	create_pipe(data);
  // print_args(data->arr_cmds[0]);
  // print_args(data->arr_cmds[1]);
	pid1 = create_fork();
	if (pid1 == 0)
		child_write_pipe(data, data->pipefd, data->arr_cmds[0]);
  wait(&pid1);
  // waitpid(pid1, NULL, 0); 
	pid2 = create_fork();
	if (pid2 == 0)
		child_read_pipe_write_file(data, data->pipefd, data->arr_cmds[1]);
	waitpid(pid2, NULL, 0); // for some reason this never finishes
  // wait(&pid2);

  terminate_on_success(data);
  return (0);
}

