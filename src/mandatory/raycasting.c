# include "../../inc/linux_inc/cub3d.h"

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
        // ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x) / CELL_SIZE;
    else
        ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y / CELL_SIZE;
        // ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y) / CELL_SIZE;
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

int get_texture_number(t_ray *ray)
{
    if (ray->is_door == 1 && ray->hit == 2)
        return (4);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        return (0);
    else if (ray->side == 0 && ray->ray_dir_x < 0)
        return (1);
    else if (ray->side == 1 && ray->ray_dir_y > 0)
        return (2);
    else if (ray->side == 1 && ray->ray_dir_y < 0)
        return (3);
    return (0);
}


void    get_texture_cordinates(t_ray *ray, t_data *data, t_cordinate *cordinate)
{
    cordinate->tex_num = get_texture_number(ray);
    if (ray->side == 0)
        cordinate->wall_x = data->player.y + (ray->perp_wall_dist * CELL_SIZE) * ray->ray_dir_y;
    else
        cordinate->wall_x = data->player.x + (ray->perp_wall_dist * CELL_SIZE) * ray->ray_dir_x;
    cordinate->wall_x = fmod(cordinate->wall_x, CELL_SIZE);
    cordinate->wall_x /= CELL_SIZE;
    cordinate->tex_x = (int)(cordinate->wall_x * data->game.image[cordinate->tex_num]->width);
    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
        cordinate->tex_x = data->game.image[cordinate->tex_num]->width - cordinate->tex_x - 1;
    cordinate->tex_step = 1.0 * (double)data->game.image[cordinate->tex_num]->height / ray->line_height;
    cordinate->tex_pos = (ray->draw_start - MAP_HEIGHT / 2 + ray->line_height / 2) * cordinate->tex_step;
    cordinate->y = ray->draw_start;
}


void draw_wall(t_ray *ray, t_data *data, int x)
{
    t_cordinate cordinate;

    get_texture_cordinates(ray, data, &cordinate);
    while (cordinate.y <= ray->draw_end)
    {
        cordinate.tex_y = (int)cordinate.tex_pos;
        if (cordinate.tex_y >= data->game.image[cordinate.tex_num]->height)
            cordinate.tex_y = data->game.image[cordinate.tex_num]->height - 1;
        cordinate.color = *(int *)(data->game.image[cordinate.tex_num]->add + cordinate.tex_y * data->game.image[cordinate.tex_num]->l_length + cordinate.tex_x * (data->game.image[cordinate.tex_num]->bp_pixels / 8));
        draw_pixel(&data->img, x, cordinate.y, cordinate.color);
        cordinate.tex_pos += cordinate.tex_step;
        cordinate.y++;
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
        // if (data->map.grid[ray.map_x][ray.map_y] == 'D')
        //     handle_door(&ray, data);
        calculate_wall_distance(&ray, &data->player);
        calculate_line_dimensions(&ray, data->img.height);
        draw_wall(&ray, data, x);
        x++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}