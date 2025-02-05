# include "../../inc/linux_inc/cub3d.h"

int game_loop(t_data *data)
{
    render(data);
    move_player(data);
    // usleep(16667); // 60fps
    return (0);
}