/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:32:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 10:46:21 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Creates an empty structure for the command.
*/
void	init_cmd_struct(t_cmd *cmd)
{
	cmd->split_string = NULL;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->len = 0;
	cmd->fd = 0;
}

/*
Creates an empty structure for the data.
Already parses the number of commands.
*/
t_data	*init_data_struct(int argc)
{
	t_data	*data;
	int		num_cmds;

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

/*
Calls the initialization of an empty data structure.
Calls the parsing process for each command passing the arguments
provided in argv.
*/
t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = init_data_struct(argc);
	data->arr_cmds[0] = parse_cmd(data, argv[2], argv[1], NULL);
	data->arr_cmds[1] = parse_cmd(data, argv[3], NULL, argv[argc - 1]);
	return (data);
}
