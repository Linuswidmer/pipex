/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:01:34 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 10:42:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Creates a new process. Returns 0 on error
*/
int	create_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (0);
	return (1);
}

/*
Creates a new pipe and stores it in the data structure. Returns 0 on error
*/
int	create_pipe(t_data *data)
{
	if (pipe(data->pipefd) == -1)
		return (0);
	return (1);
}
