# include "../../cub3d.h"

void initialize_ray(t_ray *ray, t_data *data, int x)
{
    ray->camera_x = 2.0 * x / (double)data->img.width - 1.0;
    ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
    ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
    ray->map_x = (int)data->player.x;
    ray->map_y = (int)data->player.y;
    if (ray->ray_dir_x == 0)
        ray->delta_dist_x = INFINITY;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
    if (ray->ray_dir_y == 0)
        ray->delta_dist_y = INFINITY;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void calculate_wall_distance(t_ray *ray, t_player *player)
{
    (void)player;
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x / CELL_SIZE;
    else
        ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y / CELL_SIZE;
}

void calculate_line_dimensions(t_ray *ray, int screen_height)
{
    ray->line_height = (int)(screen_height / ray->perp_wall_dist);
    ray->draw_start = (-ray->line_height / 2 + screen_height / 2);
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = (ray->line_height / 2 + screen_height / 2);
    if (ray->draw_end >= screen_height)
        ray->draw_end = screen_height - 1;
}



void raycast(t_data *data)
{
    t_ray ray;
    int x;
    
    x = 0;
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