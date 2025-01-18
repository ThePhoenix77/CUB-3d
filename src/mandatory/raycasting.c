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
    clear_screen(data, 0x000000);
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

// #include "cub3d.h"

// void initialize_ray(t_ray *ray, t_data *data, int x)
// {
//     ray->camera_x = 2.0 * x / (double)data->img.width - 1.0;
//     ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
//     ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
//     ray->map_x = (int)data->player.x;
//     ray->map_y = (int)data->player.y;
//     ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_x);
//     ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_y);

//     DEBUG_PRINTF("Initialize Ray -> x: %d, camera_x: %.2f, ray_dir_x: %.2f, ray_dir_y: %.2f\n", 
//                  x, ray->camera_x, ray->ray_dir_x, ray->ray_dir_y);
// }

// void calculate_step_and_side_dist(t_ray *ray, t_data *data)
// {
//     ray->step_x = (ray->ray_dir_x < 0) ? -1 : 1;
//     ray->side_dist_x = (ray->ray_dir_x < 0)
//         ? (data->player.x - ray->map_x) * ray->delta_dist_x
//         : (ray->map_x + 1.0 - data->player.x) * ray->delta_dist_x;

//     ray->step_y = (ray->ray_dir_y < 0) ? -1 : 1;
//     ray->side_dist_y = (ray->ray_dir_y < 0)
//         ? (data->player.y - ray->map_y) * ray->delta_dist_y
//         : (ray->map_y + 1.0 - data->player.y) * ray->delta_dist_y;

//     DEBUG_PRINTF("Step & Side Dist -> step_x: %d, step_y: %d, side_dist_x: %.2f, side_dist_y: %.2f\n",
//                  ray->step_x, ray->step_y, ray->side_dist_x, ray->side_dist_y);
// }

// void perform_dda(t_ray *ray, t_map *map)
// {
//     ray->hit = 0;
//     while (ray->hit == 0)
//     {
//         if (ray->side_dist_x < ray->side_dist_y)
//         {
//             ray->side_dist_x += ray->delta_dist_x;
//             ray->map_x += ray->step_x;
//             ray->side = 0;
//         }
//         else
//         {
//             ray->side_dist_y += ray->delta_dist_y;
//             ray->map_y += ray->step_y;
//             ray->side = 1;
//         }

//         if (map->grid[ray->map_y / CELL_SIZE][ray->map_x / CELL_SIZE] == '1')
//         {
//             ray->hit = 1;
//             DEBUG_PRINTF("Hit Wall -> map_x: %d, map_y: %d\n", ray->map_x / CELL_SIZE, ray->map_y / CELL_SIZE);
//         }
//     }
// }

// void calculate_wall_distance(t_ray *ray, t_player *player)
// {
//     ray->perp_wall_dist = (ray->side == 0)
//         ? (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x
//         : (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;

//     DEBUG_PRINTF("Wall Distance -> perp_wall_dist: %.2f\n", ray->perp_wall_dist);
// }

// void calculate_line_dimensions(t_ray *ray, int screen_height)
// {
//     // Correct line height calculation with aspect ratio adjustment
//     ray->line_height = (int)(screen_height / ray->perp_wall_dist * CELL_SIZE);

//     // Stretch the walls to fit the screen by adjusting the aspect ratio
//     if (ray->line_height > screen_height)
//         ray->line_height = screen_height; // Cap the height to the screen size

//     ray->draw_start = fmax(0, -ray->line_height / 2 + screen_height / 2);
//     ray->draw_end = fmin(screen_height - 1, ray->line_height / 2 + screen_height / 2);

//     DEBUG_PRINTF("Line Dimensions -> line_height: %d, draw_start: %d, draw_end: %d\n",
//                  ray->line_height, ray->draw_start, ray->draw_end);
// }

// void draw_wall(t_ray *ray, t_data *data, int x)
// {
//     int y;
//     int pixel;
//     int color;

//     color = (ray->side == 0) ? 0xAAAAAA : 0x777777;
//     for (y = ray->draw_start; y <= ray->draw_end; y++)
//     {
//         pixel = y * data->img.size_line + x * (data->img.bpp / 8);
//         data->img.data[pixel] = color & 0xFF;            // Blue
//         data->img.data[pixel + 1] = (color >> 8) & 0xFF; // Green
//         data->img.data[pixel + 2] = (color >> 16) & 0xFF; // Red
//     }

//     DEBUG_PRINTF("Draw Wall -> x: %d, draw_start: %d, draw_end: %d\n", x, ray->draw_start, ray->draw_end);
// }

// void clear_screen(t_data *data, int color)
// {
//     int x, y;
//     int pixel;

//     for (y = 0; y < data->img.height; y++)
//     {
//         for (x = 0; x < data->img.width; x++)
//         {
//             pixel = y * data->img.size_line + x * (data->img.bpp / 8);
//             data->img.data[pixel] = color & 0xFF;            // Blue
//             data->img.data[pixel + 1] = (color >> 8) & 0xFF; // Green
//             data->img.data[pixel + 2] = (color >> 16) & 0xFF; // Red
//         }
//     }
// }

// void raycast(t_data *data)
// {
//     t_ray ray;
//     int x;

//     // Clear the screen with a background color (e.g., black or sky blue)
//     clear_screen(data, 0x000000); // Black background

//     for (x = 0; x < data->img.width; x++)
//     {
//         initialize_ray(&ray, data, x);
//         calculate_step_and_side_dist(&ray, data);
//         perform_dda(&ray, &data->map);
//         calculate_wall_distance(&ray, &data->player);
//         calculate_line_dimensions(&ray, data->img.height);
//         draw_wall(&ray, data, x);
//     }

//     mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
//     DEBUG_PRINTF("Raycasting Completed.\n");
// }
