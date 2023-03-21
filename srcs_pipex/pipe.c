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

int count_cmd_len(char **split_string, char *file)
{
	int num_args;

	num_args = 0;
	while (split_string[num_args])
		num_args++;
  if (num_args == 0)
    return (0);
	if (file)
		num_args++;
	return (num_args);
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

int parse_input_to_args(t_cmd *cmd, char *file)
{
	char **args;
	int file_exists;
	int i;

	i = 0;
	if (file)
		file_exists = 1;
	else
		file_exists = 0;
	cmd->args = malloc(sizeof(char *) * (cmd->len + 1));
  if (!cmd->args)
    return (0);
  while (i < cmd->len - file_exists)
	{
		cmd->args[i] = ft_strdup(cmd->split_string[i]);
    if (!cmd->args[i])
    {
      free(cmd->args);
		  return (0);
    }
    i++;
	}
	if (file)
	{
		cmd->args[i] = ft_strdup(file);
    if (!cmd->args[i])
    {
      free(cmd->args);
		  return (0);
    }
		cmd->args[i + 1] = NULL;
	}
	else
		cmd->args[i] = NULL;
	return (1);
}

int parse_split_string(t_cmd *cmd, char *input)
{
  cmd->split_string = ft_split(input, ' ');
  if (!cmd->split_string)
  {
    free(cmd);
    return (0);
  }
  return (1);
}

int parse_cmd_len(t_cmd *cmd, char *infile)
{
  cmd->len = count_cmd_len(cmd->split_string, infile);
	if (cmd->len == 0)
  {
    free(cmd->split_string[0]);
    free(cmd->split_string);
    free(cmd);
    return (0);
  }
  return (1);
}

int parse_cmd_path(t_cmd *cmd)
{
	cmd->path = ft_strjoin("/bin/", cmd->args[0]);
  // printf("%s\n", cmd->path);
  // if (!cmd->path)
  // {
  //   free_split(cmd->split_string, cmd->len);
  //   free_args(cmd->args);
  //   free(cmd);
  //   return (0);
  // }
  return (1);
}

int test_access(t_cmd *cmd, int mode)
{
  if (access(cmd->path, F_OK) != 0)
  {
    free(cmd->path);
    free_split(cmd->split_string, cmd->len);
    free_args(cmd->args);
    free(cmd);
    return (0);
  }
  return (1);
}

int parse_fd_outfile(t_cmd *cmd, char *outfile)
{
	cmd->fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  if (cmd->fd == -1) 
  {
    free(cmd->path);
    free_split(cmd->split_string, cmd->len);
    free_args(cmd->args);
    free(cmd);
    return (0);
  }
  return (1);
}

t_cmd *parse_cmd(t_data *data, char *input, char *infile, char *outfile)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
  if (!cmd)
    terminate (data, "Malloc");
  if (!parse_split_string(cmd, input))
    terminate (data, "Failed to split arguments");
  if (!parse_cmd_len(cmd, infile))
    terminate (data, "invalid arguments provided");
  if (!parse_input_to_args(cmd, infile))
  {
    free_split(cmd->split_string, cmd->len);
    free(cmd);
    terminate(data, "Malloc");
  }
  if (!parse_cmd_path(cmd));
    // terminate(data, "Malloc");
  if (!test_access(cmd, F_OK));
    // terminate(data, "Path");
	if (outfile)
    if(!parse_fd_outfile(cmd, outfile));
    // terminate(data, "Open");
	return (cmd);
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

t_data *check_and_process_input(int argc, char **argv)
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

int main(int argc, char *argv[]) 
{
  pid_t pid1;
	pid_t pid2;
	t_data *data;

	data = check_and_process_input(argc, argv);
	create_pipe(data);
	pid1 = create_fork();
	if (pid1 ==0)
		first_child_process(data->pipefd, data->arr_cmds[0]);
	pid2 = create_fork();
	if (pid2 == 0)
		second_child_process(data->pipefd, data->arr_cmds[1]);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	waitpid(pid1, NULL, 0); 
	waitpid(pid2, NULL, 0);

  return (0);
}

