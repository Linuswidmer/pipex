#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../includes/pipex.h"

int check_input(int argc, char **argv)
{
  if (argc == 5)
  {
    return (1);
  }
  else
    return (0);
}

t_data *process_input(int argc, char **argv)
{
  t_data *data;

  data = malloc(sizeof(t_data));
  if (check_input(argc, argv))
  {
    data->infile = argv[1];
    data->fd_infile = open(data->infile, O_RDONLY);
    if (data->fd_infile == -1)
      perror("Error opening file");
    data->outfile = argv[4];
    data->fd_outfile = open(data->outfile, O_WRONLY);
    if (data->fd_outfile == -1)
      perror("Error opening file");
    data->cmd1 = argv[2];
    data->cmd2 = argv[3];
    return (data);
  }
  else
  {
    printf("Error\n");
    return (data);
  }
}

int main(int argc, char **argv)
{
  t_data *data;

  data = process_input(argc, argv);
  printf("Infile is %s\n", data->infile);
  printf("Outfile is %s\n", data->outfile);
  printf("Command1 is %s\n", data->cmd1);
  printf("Command2 is %s\n", data->cmd2);
  printf("fd infile is %i\n", data->fd_infile);
  printf("fd outfile is %i\n", data->fd_outfile);
}
