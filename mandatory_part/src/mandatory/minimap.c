# include "../../cub3d.h"

void player_dir(t_data *data, int player_x, int player_y)
{
    int x_end;
    int y_end;
    int steps;
    int i;
    int dot_x;
    int dot_y;
    int color;
    double dx;
    double dy;

    i = 1;
    x_end = player_x + (int)(data->player.dir_x * CELL_SIZE / 2);
    y_end = player_y + (int)(data->player.dir_y * CELL_SIZE / 2);
    steps = 10;
    // Calculate the incremental step for each dot
    dx = (x_end - player_x) / (double)steps;
    dy = (y_end - player_y) / (double)steps;
    while (i <= steps)
    {
        dot_x = player_x + (int)(dx * i);
        dot_y = player_y + (int)(dy * i);
        color = 0x00FF00 - (0x000FFF * i); // Gradually fade the color
        draw_rectangle(&data->img, dot_x - 1, dot_y - 1, 2, 2, color, MAP_WIDTH, MAP_HEIGHT);
        i++;
    }
}


void draw_minimap_tiles(t_data *data, int start_x, int start_y, int end_x, int end_y)
{
    int y = start_y;
    while (y <= end_y)
    {
        int x = start_x;
        while (x <= end_x)
        {
            if (x >= 0 && y >= 0 && y < data->map.height && 
    data->map.grid[y] != NULL && x < (int)ft_strlen(data->map.grid[y]))
            {
                int tile_x = (x - start_x) * (CELL_SIZE / MINIMAP_SCALE);
                int tile_y = (y - start_y) * (CELL_SIZE / MINIMAP_SCALE);
                draw_rectangle(
                    &data->img,
                    tile_x + 10,
                    tile_y + 10,
                    (CELL_SIZE / MINIMAP_SCALE),
                    (CELL_SIZE / MINIMAP_SCALE),
                    color_cell_matching(data->map.grid[y][x]),
                    MINIMAP_WIDTH,
                    MINIMAP_HEIGHT
                );
            }
            x++;
        }
        y++;
    }
}

void draw_player_on_minimap(t_data *data)
{
    int player_minimap_x;
    int player_minimap_y;

    player_minimap_x = (MINIMAP_WIDTH / 2) - 2;
    player_minimap_y = (MINIMAP_HEIGHT / 2) - 2;
    draw_rectangle(
        &data->img,
        player_minimap_x + 10,
        player_minimap_y + 10,
        4,
        4,
        0xFF00FF,
        MINIMAP_WIDTH,
        MINIMAP_HEIGHT
    );
    player_dir(data, player_minimap_x + 12, player_minimap_y + 12);
}

void draw_minimap_frame(t_data *data)
{
    int frame_color;
    int frame_thickness;

    frame_thickness = 5;
    frame_color = MINIMAP_FRAME_COLOR; // Golden color
    draw_rectangle(
        &data->img,
        10 - frame_thickness,
        10 - frame_thickness,
        MINIMAP_WIDTH + (2 * frame_thickness),
        MINIMAP_HEIGHT + (2 * frame_thickness),
        frame_color,
        data->img.width,
        data->img.height
    );
    draw_rectangle(
        &data->img,
        10,
        10,
        MINIMAP_WIDTH,
        MINIMAP_HEIGHT,
        0x000000,
        data->img.width,
        data->img.height
    );
}

void render_minimap(t_data *data)
{
    int viewport_start_x;
    int viewport_start_y;
    int viewport_end_x;
    int viewport_end_y;

    calculate_viewport(data, &viewport_start_x, &viewport_start_y, &viewport_end_x, &viewport_end_y);
    draw_minimap_frame(data);
    draw_minimap_tiles(data, viewport_start_x, viewport_start_y, viewport_end_x, viewport_end_y);
    draw_player_on_minimap(data);
}
