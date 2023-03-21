/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:01:34 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/20 16:01:52 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void print_args(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->len)
	{
		printf("%s\n", cmd->args[i]);
		i++;
	}
}

pid_t create_fork()
{
	pid_t pid;

	pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
	return (pid); 
	
}

void create_pipe(t_data *data)
{
    if (pipe(data->pipefd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}
