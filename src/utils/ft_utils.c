# include "../../inc/linux_inc/cub3d.h"

void quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}