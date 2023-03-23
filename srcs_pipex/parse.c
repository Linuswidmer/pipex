#include "pipex.h"

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
		  return (0);
    i++;
	}
	if (file)
	{
		cmd->args[i] = ft_strdup(file);
    if (!cmd->args[i])
		  return (0);
	}
  cmd->args[i + file_exists] = NULL;
	return (1);
}


t_cmd *parse_cmd(t_data *data, char *input, char *infile, char *outfile)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
  init_cmd_struct(cmd);
  if (!cmd)
    terminate_on_error(data, NULL, "Malloc");
  if (!parse_split_string(cmd, input))
    terminate_on_error(data, cmd, "Failed to split arguments");
  if (!parse_cmd_len(cmd, infile))
    terminate_on_error(data, cmd, "invalid arguments provided");
  if (!parse_input_to_args(cmd, infile))
    terminate_on_error(data, cmd, "Malloc");
  if (!parse_cmd_path(cmd))
    terminate_on_error(data, cmd, "Malloc");
  if (access(cmd->path, F_OK) != 0)
    terminate_on_error(data, cmd, "Path");
  if (outfile)
  {
    if(!parse_fd_outfile(cmd, outfile))
      terminate_on_error(data, cmd, "Open");
  }
  return (cmd);
}
