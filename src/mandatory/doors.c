# include "../../inc/linux_inc/cub3d.h"

void handle_door(t_ray *ray, t_data *data)
{
    if (data->map.grid[ray->map_x][ray->map_y] == 'D')
    {
        if (data->player.door_open == 0)
            data->player.door_open = 1;
        else
            data->player.door_open = 0;
    }
}