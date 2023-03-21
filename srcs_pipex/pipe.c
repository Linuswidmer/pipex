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

void first_child_process(int *pipefd, t_cmd *cmd)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    execve(cmd->path, cmd->args, NULL);
    perror("execve");
    exit(EXIT_FAILURE);
}

void second_child_process(int *pipefd, t_cmd *cmd)
{
  int fd;

  close(pipefd[1]); 
  dup2(pipefd[0], STDIN_FILENO); 
  dup2(cmd->fd, STDOUT_FILENO);
  execve(cmd->path, cmd->args, NULL);
  perror("execve");
  exit(EXIT_FAILURE);
}


void process_num_cmds(t_data *data, int argc)
{
  if (argc == 5)
	  data->num_cmds = argc - 3;
  else
  {
    data->num_cmds = 0;
    terminate(data, "Invalid number of cmds");
  }
}


t_data *init_data_struct(int argc)
{
	t_data *data;
	int num_cmds;

	data = malloc(sizeof(t_data));
  if (!data)
    terminate(data, "Malloc");
	process_num_cmds(data, argc);
	data->arr_cmds = malloc(sizeof(t_cmd *) * data->num_cmds);
	if (!data->arr_cmds)
	  terminate(data, "Malloc");
  return (data);
}

t_data *init(int argc, char **argv)
{
	t_data *data;
	int i;
  char *infile;
  char *outfile;

	i = 0;
	data = init_data_struct(argc);
  infile = argv[1];
  outfile = argv[argc - 1];
	data->arr_cmds[0] = parse_cmd(data, argv[2], infile, NULL);
	data->arr_cmds[1] = parse_cmd(data, argv[3], NULL, outfile);
	return (data);	

}

int main(int argc, char *argv[]) 
{
  pid_t pid1;
	pid_t pid2;
	t_data *data;

	data = init(argc, argv);
	create_pipe(data);
	pid1 = create_fork();
	if (pid1 == 0)
		first_child_process(data->pipefd, data->arr_cmds[0]);
	pid2 = create_fork();
	if (pid2 == 0)
		second_child_process(data->pipefd, data->arr_cmds[1]);
	close(data->arr_cmds[1]->fd);
  close(data->pipefd[0]);
	close(data->pipefd[1]);
	waitpid(pid1, NULL, 0); 
	waitpid(pid2, NULL, 0);

  free_cmd_struct(data->arr_cmds[0]);
  free_cmd_struct(data->arr_cmds[1]);
  terminate(data, NULL);
  return (0);
}

