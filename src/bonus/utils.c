# include "../../inc/linux_inc/cub3d.h"

int game_loop(t_data *data)
{
    // auto_close_doors(&data->map);
    render(data);
    move_player(data);
    // usleep(16667); // 60fps
    return (0);
}