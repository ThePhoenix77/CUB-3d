#include "cub3d.h"

void put_pixel(t_data *data, int x, int y, int color)
{
    int *dst;

    dst = data->addr + (y * data->line_length / 4 + x);  // Use / 4 bc it's int
    *dst = color;
}

void render_tile(t_data *data, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE - 1)
    {
        j = 0;
        while (j < TILE_SIZE - 1)
        {
            put_pixel(data, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
            j++;
        }
        i++;
    }
}

void render_map(t_data *data)
{
    int x;
    int y;
    int color;

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '1')
                color = 0xFFFFFF; // White for walls
            else if (data->map[y][x] == '0')
                color = 0x000000; // Black for empty space
            else if (data->map[y][x] == 'P')
                color = 0xFF0000; // Red for the player
            else
                color = 0x00FF00; // Green for any other character
            render_tile(data, x, y, color);
            x++;
        }
        y++;
    }
}