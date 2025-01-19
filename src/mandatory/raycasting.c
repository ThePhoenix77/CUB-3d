#include "cub3d.h"

void initialize_ray(t_ray *ray, t_data *data, int x)
{
    ray->camera_x = 2.0 * x / (double)data->img.width - 1.0;
    ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
    ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
    ray->map_x = (int)data->player.x;
    ray->map_y = (int)data->player.y;
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_y);
}

void calculate_wall_distance(t_ray *ray, t_player *player)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void calculate_line_dimensions(t_ray *ray, int screen_height)
{
    ray->line_height = (int)(screen_height / ray->perp_wall_dist * 40);
    ray->draw_start = (-ray->line_height / 2 + screen_height / 2);
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = (ray->line_height / 2 + screen_height / 2);
    if (ray->draw_end >= screen_height)
        ray->draw_end = screen_height - 1;
}

void draw_wall(t_ray *ray, t_data *data, int x)
{
    int y;
    int pixel;
    int color;

    y = ray->draw_start;
    color = 0x000000;
    if (ray->side == 0)
        color = 0x777777;
    else
        color = 0xAAAAAA;
    while (y <= ray->draw_end)
    {
        pixel = y * data->img.size_line + x * (data->img.bpp / 8);
        data->img.data[pixel] = color & 0xFF;
        data->img.data[pixel + 1] = (color >> 8) & 0xFF;
        data->img.data[pixel + 2] = (color >> 16) & 0xFF;
        y++;
    }
}

void raycast(t_data *data)
{
    t_ray ray;
    int x;
    
    x = 0;
    // clear_screen(data, 0x000000);
    while (x < data->img.width)
    {
        initialize_ray(&ray, data, x);
        calculate_step_and_side_dist(&ray, data);
        perform_dda(&ray, &data->map);
        calculate_wall_distance(&ray, &data->player);
        calculate_line_dimensions(&ray, data->img.height);
        draw_wall(&ray, data, x);
        x++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}