# include "../../inc/linux_inc/cub3d.h"

int handle_mouse_move(int x, int y, void *param)
{ // need to follow this format "int (*f)(int x, int y, void *param)"
    (void)y;
    t_data *data;
    int delta_x;
    
    data = (t_data *)param;
    if (data->player.first_time)
    {
        data->player.prev_x = x;
        data->player.first_time = 0;
        return (0);
    }
    delta_x = x - data->player.prev_x;

    if (delta_x < 0)
        rotate_left(&data->player);
    else if (delta_x > 0)
        rotate_right(&data->player);

    data->player.prev_x = x;

    return (0);
}

void setup_mouse_rotation(t_data *data)
{
    mlx_hook(data->win, 6, 1L << 6, handle_mouse_move, data);
    // mlx_mouse_hide(data->mlx, data->win); // Fix: Pass correct arguments
}