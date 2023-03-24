/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:16:26 by lwidmer           #+#    #+#             */
/*   Updated: 2023/03/24 10:23:24 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cmd {
	char	**split_string;
	char	**args;
	char	*path;
	int		len;
	int		fd;
}	t_cmd;

typedef struct s_data {
	int		pipefd[2];
	int		num_cmds;
	t_cmd	**arr_cmds;
}	t_data;

/* libft */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/* pipe_utils */
int		create_fork(pid_t *pid);
int		create_pipe(t_data *data);

/* terminate */
void	terminate_on_error(t_data *data, t_cmd *cmd, char *str);
void	terminate_on_success(t_data *data);

/* terminate_utils */
void	free_split(char **split_str, int len);
void	free_args(char **args);
void	free_cmd_struct(t_cmd *cmd);
void	free_data_struct(t_data *data);

/* parse */
t_cmd	*parse_cmd(t_data *data, char *input, char *infile, char *outfile);

/* parse_utils */

int		parse_split_string(t_cmd *cmd, char *input);
int		parse_cmd_len(t_cmd *cmd, char *infile);
int		parse_cmd_path(t_cmd *cmd);
int		parse_fd_outfile(t_cmd *cmd, char *outfile);
void	parse_num_cmds(t_data *data, int argc);

/* init */
void	init_cmd_struct(t_cmd *cmd);
t_data	*init(int argc, char **argv);
#endif
