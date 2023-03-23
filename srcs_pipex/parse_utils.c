#include "pipex.h"


void parse_num_cmds(t_data *data, int argc)
{
  if (argc == 5)
	  data->num_cmds = argc - 3;
  else
  {
    data->num_cmds = 0;
    terminate_on_error(data, NULL, "Invalid number of cmds");
  }
}

int parse_split_string(t_cmd *cmd, char *input)
{
  cmd->split_string = ft_split(input, ' ');
  if (!cmd->split_string)
    return (0);
  return (1);
}

int parse_cmd_len(t_cmd *cmd, char *infile)
{
	int num_args;
  char **split_string;

  split_string = cmd->split_string;
	num_args = 0;
	while (split_string[num_args])
		num_args++;
  if (num_args == 0)
    return (0);
	if (infile)
		num_args++;
  cmd->len = num_args;
	return (1);
}

int parse_cmd_path(t_cmd *cmd)
{
	cmd->path = ft_strjoin("/bin/", cmd->args[0]);
  if (!cmd->path)
    return (0);
  return (1);
}

int parse_fd_outfile(t_cmd *cmd, char *outfile)
{
	cmd->fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  if (cmd->fd == -1 || cmd->fd == 0) 
    return (0);
  return (1);
}
