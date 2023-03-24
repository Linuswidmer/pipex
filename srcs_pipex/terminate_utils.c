/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:22:13 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 10:44:48 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
All functions here are pretty much self-explanatory by their name.
*/
void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_split(char **split_str, int len)
{
	int	i;

	i = 0;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str);
}

void	free_cmd_struct(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	if (cmd->split_string)
		free_split(cmd->split_string, cmd->len);
	if (cmd->args)
		free_args(cmd->args);
	if (cmd)
		free(cmd);
}

void	free_data_struct(t_data *data)
{
	if (data->num_cmds > 0)
		free (data->arr_cmds);
	if (data)
		free (data);
}
