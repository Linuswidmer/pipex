#include "pipex.h"


void free_args(char **args)
{
  int i;

  i = 0;
  while (args[i])
  {
    free(args[i]);
    i++;
  }
  free(args);
}

void free_split(char **split_str, int len)
{
  int i;

  i = 0;
  while (split_str[i])
  {
    free(split_str[i]);
    i++;
  }
  free(split_str);
}

void free_cmd_struct(t_cmd *cmd)
{
  if (cmd->path)
    free(cmd->path);
  if(cmd->split_string)
    free_split(cmd->split_string, cmd->len);
  if (cmd->args)
    free_args(cmd->args);
  if (cmd)
    free(cmd);
}

void free_data_struct(t_data *data)
{
  // if (data->pipefd)
  // {
  //   close(data->pipefd[0]);
	 //  close(data->pipefd[1]);
  // }
  if (data->num_cmds > 0)
    free (data->arr_cmds);
  if (data)
    free (data);
}

void terminate_on_success(t_data *data)
{
	close(data->arr_cmds[1]->fd);
  close(data->pipefd[0]);
	close(data->pipefd[1]);
  free_cmd_struct(data->arr_cmds[0]);
  free_cmd_struct(data->arr_cmds[1]);
  free_data_struct(data);
}

void terminate_on_error(t_data *data,t_cmd *cmd, char *str)
{
  if (data)
  {
    if (data->arr_cmds[0])
      free_cmd_struct(data->arr_cmds[0]);
    if (data->arr_cmds[1])
      free_cmd_struct(data->arr_cmds[1]);
    if (cmd)
      free_cmd_struct(cmd);
    if (data)
      free_data_struct(data);
  }
  if (str)
      perror(str);
  exit (0);
}
