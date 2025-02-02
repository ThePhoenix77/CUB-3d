# include "../../inc/linux_inc/cub3d.h"

void calculate_viewport(t_data *data, int *start_x, int *start_y, int *end_x, int *end_y)
{
    int player_x;
    int player_y;

    player_x = (int)(data->player.x / CELL_SIZE);
    player_y = (int)(data->player.y / CELL_SIZE);
    *start_x = player_x - (MINIMAP_WIDTH / (2 * (CELL_SIZE / MINIMAP_SCALE)));
    *start_y = player_y - (MINIMAP_HEIGHT / (2 * (CELL_SIZE / MINIMAP_SCALE)));
    *end_x = player_x + (MINIMAP_WIDTH / (2 * (CELL_SIZE / MINIMAP_SCALE)));
    *end_y = player_y + (MINIMAP_HEIGHT / (2 * (CELL_SIZE / MINIMAP_SCALE)));
}

void ceil_and_floor_filling(t_data *data, int x, int y, double floor_x, double floor_y, double floor_step_x, double floor_step_y)
{
    while (x < data->img.width)
    {
        floor_x += floor_step_x;
        floor_y += floor_step_y;
        if (y < data->img.height / 2)
            draw_pixel(&data->img, x, y, data->game.c_ceiling);
        else
            draw_pixel(&data->img, x, y, data->game.c_floor);
        x++;
    }
}
void ceil_and_floor_filling2(t_data *data, int x, int y, double row_distance)
{
    double ray_dir_x0;
    double ray_dir_y0;
    double ray_dir_x1;
    double ray_dir_y1;
    double floor_step_x;
    double floor_step_y;
    double floor_x;
    double floor_y;

    // Direction of the rays at the edges of the screen
    ray_dir_x0 = data->player.dir_x - data->player.plane_x;
    ray_dir_y0 = data->player.dir_y - data->player.plane_y;
    ray_dir_x1 = data->player.dir_x + data->player.plane_x;
    ray_dir_y1 = data->player.dir_y + data->player.plane_y;
    // Calculate the floor and ceiling ray directions
    floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / data->img.width;
    floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / data->img.width;
    floor_x = data->player.x + row_distance * ray_dir_x0; // distance from the floor or cieling
    floor_y = data->player.y + row_distance * ray_dir_y0;
    ceil_and_floor_filling(data, x, y, floor_x, floor_y, floor_step_x, floor_step_y);
    
}

void render_ceiling_and_floor(t_data *data)
{
    int x;
    int y;
    double row_distance;
    
    x = 0;
    y = 0;
    row_distance = 0;
    while (y < data->img.height)
    {
        x = 0;
        row_distance = 0.5 * data->img.height / (data->img.height - y);
        ceil_and_floor_filling2(data, x, y, row_distance);
        y++;
    }
}