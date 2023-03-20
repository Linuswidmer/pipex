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

void second_child_process(int *pipefd, t_cmd *cmd, char *outfile)
{
  int fd;

  close(pipefd[1]); 
  dup2(pipefd[0], STDIN_FILENO); 
  fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  if (fd == -1) 
  {
    perror("open");
    exit(EXIT_FAILURE);
  }
  dup2(fd, STDOUT_FILENO);
  execve(cmd->path, cmd->args, NULL);
  perror("execve");
  exit(EXIT_FAILURE);

}

char **process_input_to_args(char **split_string, char *file, int cmd_len)
{
	char **args;
	int file_exists;
	int i;

	i = 0;
	if (file)
		file_exists = 1;
	else
		file_exists = 0;
	args = malloc(sizeof(char *) * (cmd_len + 1));
	while (i < cmd_len - file_exists)
	{
		args[i] = ft_strdup(split_string[i]);
		i++;
	}
	if (file)
	{
		args[i] = ft_strdup(file);
		args[i + 1] = NULL;
	}
	else
		args[i] = NULL;
	return (args);
}

int count_cmd_len(char **split_string, char *file)
{
	int num_args;

	num_args = 0;
	while (split_string[num_args])
		num_args++;
	if (file)
		num_args++;
	return (num_args);
}

int count_num_cmds(int argc)
{
	return (argc - 3);
}

t_cmd *cmd_creator(char *input, char *file)
{
	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd));
	cmd->split_string = ft_split(input, ' ');
	cmd->len = count_cmd_len(cmd->split_string, file);
	cmd->args = process_input_to_args(cmd->split_string, file, cmd->len);
	cmd->path = ft_strjoin("/bin/", cmd->args[0]);
	if (file)
	{
		cmd->fd = malloc(sizeof(int));
		*(cmd->fd) = open()
	return (cmd);
}

t_data *init_data_struct(int argc)
{
	t_data *data;
	int num_cmds;
	
	data = malloc(sizeof(t_data));
	if (data)
	{
		data->num_cmds = count_num_cmds(argc);
		data->arr_cmds = malloc(sizeof(t_cmd *) * num_cmds);
		if (!data->arr_cmds)
		{
			free(data);
			return (NULL);
		}
	}
	return (data);
}


t_data *process_input(int argc, char **argv)
{
	t_data *data;
	int i;

	i = 0;
	data = init_data_struct(argc);
	if (data)
	{
		data->arr_cmds[0] = cmd_creator(argv[2], argv[1]);
		data->arr_cmds[1] = cmd_creator(argv[3], NULL);
	}
	return (data);	
}

void print_args(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->len)
	{
		printf("%s\n", cmd->args[i]);
		i++;
	}
}

int main(int argc, char *argv[]) {
    pid_t pid1;
	pid_t pid2;
	t_data *data;

	data = process_input(argc, argv);
	if (data->arr_cmds[0] && data->arr_cmds[1])
	{
		//print_args(data->arr_cmds[0]);
		//print_args(data->arr_cmds[1]);
		create_pipe(data);
		pid1 = create_fork();
		if (pid1 ==0)
			first_child_process(data->pipefd, data->arr_cmds[0]);
		pid2 = create_fork();
		if (pid2 == 0)
			second_child_process(data->pipefd, data->arr_cmds[1], argv[4]);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		waitpid(pid1, NULL, 0); 
		waitpid(pid2, NULL, 0);
	}
	//terminate(data);
    return 0;
}

/*
void terminate(t_data *data)
{
	int i;

	i = 0;
	if (data->arr_cmds[0])
	{
		while (i <= *(data->num_args_cmd1))
		{
			free(data->arr_cmds[0][i]);
			i++;
		}
		free(data->arr_cmds[0]);
	}
	i = 0;
	if (data->arr_cmds[1])
	{
		while (i <= *(data->num_args_cmd2))
		{
			free(data->arr_cmds[1][i]);
			i++;
		}
		free(data->arr_cmds[2]);
	}
	free(data->arr_cmds);
	free(data->num_args_cmd1);
	free(data->num_args_cmd2);
	free(data);
}
*/
