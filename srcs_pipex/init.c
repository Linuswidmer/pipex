#include "pipex.h"

void init_cmd_struct(t_cmd *cmd)
{
  cmd->split_string = NULL;
  cmd->args = NULL;
  cmd->path = NULL;
  cmd->len = 0;
  cmd->fd = 0;
}

t_data *init_data_struct(int argc)
{
	t_data *data;
	int num_cmds;

	data = malloc(sizeof(t_data));
  if (!data)
    terminate_on_error(data, NULL, "Malloc");
	parse_num_cmds(data, argc);
	data->arr_cmds = malloc(sizeof(t_cmd *) * data->num_cmds);
  data->arr_cmds[0] = NULL;
  data->arr_cmds[1] = NULL;
	if (!data->arr_cmds)
	  terminate_on_error(data, NULL, "Malloc");
  return (data);
}

t_data *init(int argc, char **argv)
{
	t_data *data;
  t_cmd *cmd1;
  t_cmd *cmd2;
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
