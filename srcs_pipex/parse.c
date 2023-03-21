#include "pipex.h"

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
  if (!cmd->path)
  {
    free_split(cmd->split_string, cmd->len);
    free_args(cmd->args);
    free(cmd);
    return (0);
  }
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
	}
  cmd->args[i + file_exists] = NULL;
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
