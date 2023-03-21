/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:16:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/17 17:47:44 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_cmd {
	char **split_string;
	char **args;
	char *path;
	int len;
	int fd;
} t_cmd;

typedef struct s_data {
	int pipefd[2];
	int num_cmds;
	t_cmd **arr_cmds;
}	t_data;

/* libft */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/* pipe_utils */
pid_t create_fork();
void create_pipe(t_data *data);

/* terminate */
void free_split(char **split_str, int len);
void free_args(char **args);
void terminate(t_data *data, char *str);

#endif
