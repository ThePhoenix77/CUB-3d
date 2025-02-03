# include "../../inc/linux_inc/cub3d.h"

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

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    unsigned char *dst = img->data + (y * img->size_line + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

int     get_texture_number(t_ray *ray)
{
    if (ray->side == 0 && ray->ray_dir_x > 0)
        return (0);
    else if (ray->side == 0 && ray->ray_dir_x < 0)
        return (1);
    else if (ray->side == 1 && ray->ray_dir_y > 0)
        return (2);
    else
        return (3);
}

void draw_wall(t_ray *ray, t_data *data, int x)
{
    int y;
    int color;
    int tex_num;
    float wall_x;
    int tex_x, tex_y;
    float tex_step, tex_pos;

    tex_num = get_texture_number(ray);
    // printf("texture number is [%d]\n", tex_num);
    if (ray->side == 0) // Horizontal wall (east or west)
        wall_x = data->player.y + ray->perp_wall_dist * ray->ray_dir_y;
    else // Vertical wall (north or south)
        wall_x = data->player.x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * data->game.image[tex_num]->width);
    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = data->game.image[tex_num]->width - tex_x - 1;
    // printf("Column[%d]: wall_x = %f, tex_x = %d, tex_step = %f, tex_pos = %f\n", x, wall_x, tex_x, tex_step, tex_pos);
    // printf("wall_x: %f, tex_x: %d\n", wall_x, tex_x);
    tex_step = (float)data->game.image[tex_num]->height / ray->line_height;
    tex_pos = (ray->draw_start - MAP_HEIGHT / 2 + ray->line_height / 2) * tex_step;
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        tex_y = (int)tex_pos;
        if (tex_y >= data->game.image[tex_num]->height)
            tex_y = data->game.image[tex_num]->height - 1;
        tex_pos += tex_step;
        color = *(int *)(data->game.image[tex_num]->add + tex_y * data->game.image[tex_num]->line_length + tex_x * (data->game.image[tex_num]->bits_per_pixel / 8));
        // color = (tex_x * 255 / data->game.image[tex_num]->width) << 16; // Red gradient
        // if (ray->side == 1) color = (color >> 1) & 8355711;
        my_mlx_pixel_put(&data->img, x, y, color);
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
        // printf("Ray[%d]: dir_x = %f, dir_y = %f | perp_wall_dist = %f | side = %d | line_height = %d | draw_start = %d | draw_end = %d\n",
        // x, ray.ray_dir_x, ray.ray_dir_y, ray.perp_wall_dist, ray.side, ray.line_height, ray.draw_start, ray.draw_end);

        draw_wall(&ray, data, x);
        x++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}