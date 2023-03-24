/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:37:28 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 11:32:50 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Computes the number of arguments for the command.
Saves a pointer to each argument inside of cmd->args and then null terminates.
If a file is provided as input to the command, this is saved as an argument.
*/
int	parse_input_to_args(t_cmd *cmd, char *file)
{
	int		file_exists;
	int		i;

	i = 0;
	file_exists = 0;
	if (file)
		file_exists = 1;
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

/*
Orchestrates the parsing of the command.
If any of the parsing functions fails (returns 0) program will be exited with 
terminate_on_error, printing the reason to STD_ERR
*/
t_cmd	*parse_cmd(t_data *data, char *input, char *infile, char *outfile)
{
	t_cmd	*cmd;

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
		if (!parse_fd_outfile(cmd, outfile))
			terminate_on_error(data, cmd, "Open");
	}
	return (cmd);
}
