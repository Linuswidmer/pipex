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
  while (i < len)
  {
    free(split_str[i]);
    i++;
  }
  free(split_str);
}

void free_cmd_struct(t_cmd *cmd)
{
  free(cmd->path);
  free_split(cmd->split_string, cmd->len);
  free_args(cmd->args);
  free(cmd);
}

void terminate(t_data *data, char *str)
{
  if (data)
  {
    if (data->num_cmds)
    {
      free(data->arr_cmds);
    }
    free(data);
  }
  if (str)
    perror(str);
  exit (0);
}

// void terminate(t_data *data)
// {
// 	int i;
//
// 	i = 0;
// 	if (data->arr_cmds[0])
// 	{
// 		while (i <= *(data->num_args_cmd1))
// 		{
// 			free(data->arr_cmds[0][i]);
// 			i++;
// 		}
// 		free(data->arr_cmds[0]);
// 	}
// 	i = 0;
// 	if (data->arr_cmds[1])
// 	{
// 		while (i <= *(data->num_args_cmd2))
// 		{
// 			free(data->arr_cmds[1][i]);
// 			i++;
// 		}
// 		free(data->arr_cmds[2]);
// 	}
// 	free(data->arr_cmds);
// 	free(data->num_args_cmd1);
// 	free(data->num_args_cmd2);
// 	free(data);
// }
