# include "cub3d.h"

int game_loop(t_data *data)
{
    // ppos(&data->player);
    printf("0\n");
    render(data);
    printf("1\n");
    raycast(data);
    printf("2\n");
    move_player(data);
    printf("3\n");
    // mlx_do_sync(data->mlx);
    // mlx_clear_window(data->mlx, data->win);
    usleep(16667); // 60fps
    return (0);
}