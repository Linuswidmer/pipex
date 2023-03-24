/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:15:30 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 11:31:58 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
All functions here are pretty much self explanatory by their name.
On error they return 0.
*/
void	parse_num_cmds(t_data *data, int argc)
{
	data->num_cmds = argc - 3;
}

int	parse_split_string(t_cmd *cmd, char *input)
{
	cmd->split_string = ft_split(input, ' ');
	if (!cmd->split_string)
		return (0);
	return (1);
}

int	parse_cmd_len(t_cmd *cmd, char *infile)
{
	int		num_args;
	char	**split_string;

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

int	parse_cmd_path(t_cmd *cmd)
{
	cmd->path = ft_strjoin("/bin/", cmd->args[0]);
	if (!cmd->path)
		return (0);
	return (1);
}

int	parse_fd_outfile(t_cmd *cmd, char *outfile)
{
	cmd->fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd == -1 || cmd->fd == 0)
		return (0);
	return (1);
}
