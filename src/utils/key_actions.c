#include "cub3d.h"

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

// [esc]: 53 || 65307
// [-->]: 124 || 65363
// [<--]: 123 || 65361
// [W]: 13 || 119
// [S]: 1 || 115
// [A]: 0 || 97
// [D]: 2 || 100


int	key_press(int key, t_data *data)
{
    if (key == 53 || key == 65307) // ESC (in macOS: 53, in Linux: 65307)
        close_window(data);
    // else if (key == 123 || key == 65361) // Left <--
    //     rotate_player(data, -0.1); // Rotate left (negative angle)
    // else if (key == 124 || key == 65363) // Right -->
    //     rotate_player(data, 0.1);  // Rotate right (positive angle)
    // else if (key == 13 || key == 119) // W
    //     move_player(data, data->dir_x * 0.1, data->dir_y * 0.1);
    // else if (key == 1 || key == 115) // S
    //     move_player(data, -data->dir_x * 0.1, -data->dir_y * 0.1);
    // else if (key == 0 || key == 97) // A
    //     move_player(data, -data->plane_x * 0.1, -data->plane_y * 0.1);
    // else if (key == 2 || key == 100) // D
    //     move_player(data, data->plane_x * 0.1, data->plane_y * 0.1);
    
     // Redraw
    //  mlx_clear_window(data->mlx, data->win);
    // render_map(data);
    // mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}