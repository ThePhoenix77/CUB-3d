#include "cub3d.h"

void put_pixel_to_image(t_img *img, int x, int y, int color, int img_width, int img_height)
{
    char *dst;

    // Ensure coordinates are within the bounds of the image
    if (x >= 0 && y >= 0 && x < img_width && y < img_height)
    {
        dst = img->data + (y * img->size_line + x * (img->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

int color_cell_matching(char cell)
{
    if (cell == '1')
        return (0xFFFFFF); // White (wall)
    if (cell == '0')
        return (0x000000); // Black (empty space)
    if (cell == 'N')
        return (0xFF0000); // Red (player position)
    return (0x0000FF); // Blue (unknown)
}

void draw_rectangle(t_img *img, int x, int y, int width, int height, int color, int img_width, int img_height)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            put_pixel_to_image(img, x + j, y + i, color, img_width, img_height);
            j++;
        }
        i++;
    }
}

void render_map(t_data *data)
{
    int x;
    int y;
    int img_width;
    int img_height;
    int color;

    y = 0;
    img_width = data->map.width * CELL_SIZE;
    img_height = data->map.height * CELL_SIZE;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            color = color_cell_matching(data->map.grid[y][x]);
            draw_rectangle(&data->img, x * (CELL_SIZE), y * (CELL_SIZE),
                           CELL_SIZE, CELL_SIZE, color, img_width, img_height);
            x++;
        }
        y++;
    }
}

void render_player(t_data *data)
{
    int player_x;
    int player_y;
    int player_size;
    int player_color;
    int line_color;
    int x_end;
    int y_end;

    player_x = (int)(data->player.x);
    player_y = (int)(data->player.y);
    player_size = 10;
    player_color = 0xFF0000;
    line_color = 0x00FF00;

    // Debugging output
    // printf("Rendering player at: X = %d, Y = %d\n", player_x, player_y);

    // bounds check
    if (player_x >= 0 && player_x < data->map.width * 32 &&
        player_y >= 0 && player_y < data->map.height * 32)
    {
        // draw player rectangle
        draw_rectangle(&data->img, player_x - player_size / 2, player_y - player_size / 2,
                       player_size, player_size, player_color, data->map.width * 32, data->map.height * 32);

        // Draw player direction line
        x_end = player_x + (int)(data->player.dir_x * 32);
        y_end = player_y + (int)(data->player.dir_y * 32);
        draw_line(&data->img, player_x, player_y, x_end, y_end, line_color);
    }
    else
    {
        printf("Player is out of bounds for rendering.\n");
    }
}


// put_pixel_to_image(t_img *img, int x, int y, int color, int img_width, int img_height)
void clear_img(t_data *data)
{
    int i;
    int j;
    int color;

    i = 0;
    color = 0x000000;
    while (i < data->map.width)
    {
        j = 0;
        while (j < data->map.height)
        {
            put_pixel_to_image(&data->img, i, j, color, data->map.width, data->map.height);
            j++;
        }
        i++;
    }
    // printf("touti l mondo !\n");
}

void render(t_data *data)
{
    // clear_img(data);
    // mlx_clear_window(data->mlx, data->win);
    render_map(data);    // Draw the map
    render_player(data); // Draw the player
    // clear_img(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
    // mlx_clear_window(data->mlx, data->win);
}
