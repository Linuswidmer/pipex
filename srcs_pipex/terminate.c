/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:44:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 11:26:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
frees all memory as expected when allocation, child process etc. 
execute as intended.
*/
void	terminate_on_success(t_data *data)
{
	close(data->arr_cmds[1]->fd);
	free_cmd_struct(data->arr_cmds[0]);
	free_cmd_struct(data->arr_cmds[1]);
	free_data_struct(data);
}

/*
tests if memory has been allocated already to avoid invalid frees.
Prints the message passed to it to STD_ERROR.
*/
void	terminate_on_error(t_data *data, t_cmd *cmd, char *str)
{
	if (data)
	{
		if (data->arr_cmds[0])
			free_cmd_struct(data->arr_cmds[0]);
		if (data->arr_cmds[1])
		{
			if (data->arr_cmds[1]->fd)
				close(data->arr_cmds[1]->fd);
			free_cmd_struct(data->arr_cmds[1]);
		}
		if (cmd)
			free_cmd_struct(cmd);
		if (data)
			free_data_struct(data);
	}
	if (str)
		perror(str);
	exit (0);
}
