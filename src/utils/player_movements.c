#include "cub3d.h"

// void rotate_player(t_data *data, double angle)
// {
//     // double old_dir_x;
//     double old_plane_x;

//     // old_dir_x = data->dir_x;
//     old_plane_x = data->plane_x;

//     data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
//     data->dir_y = data->dir_x * sin(angle) - data->dir_y * cos(angle);

//     data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
//     data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
// }

// void move_player(t_data *data, double move_x, double move_y)
// {
//     if (data->map[(int)(data->p_y)][(int)(data->p_x + move_x)] == '0')
//         data->p_x += move_x;
//     if (data->map[(int)(data->p_y + move_y)][(int)(data->p_x)] == '0')
//         data->p_y += move_y;
// }

