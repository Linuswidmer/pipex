#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data {
  char *infile;
  char *outfile;
  int fd_infile;
  int fd_outfile;
  char *cmd1;
  char *cmd2;
} t_data;

#endif
