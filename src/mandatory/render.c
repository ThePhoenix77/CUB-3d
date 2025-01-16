#include "cub3d.h"

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

int bound_check(t_data *data, int player_x, int player_y)
{
    return (player_x >= 0 && player_x < data->map.width * 32 &&
        player_y >= 0 && player_y < data->map.height * 32);
}

void player_dir(t_data *data, int player_x, int player_y)
{
    int x_end;
    int y_end;

    x_end = player_x + (int)(data->player.dir_x * CELL_SIZE / 1.5);
    y_end = player_y + (int)(data->player.dir_y * CELL_SIZE / 1.5);
    draw_line(&data->img, player_x, player_y, x_end, y_end, 0x00FF00);
}

void render_player(t_data *data)
{
    int player_x;
    int player_y;
    int player_size;
    int player_color;

    player_size = 10;
    player_color = 0xFF0000;
    player_x = (int)(data->player.x);
    player_y = (int)(data->player.y);
    // printf("Rendering player at: X = %d, Y = %d\n", player_x, player_y);
    // bounds
    if (bound_check(data, player_x, player_y))
    {
        // player rectangle
        draw_rectangle(&data->img, player_x - player_size / 2, player_y - player_size / 2,
                       player_size, player_size, player_color, data->map.width * 32, data->map.height * 32);
        // player direction
        player_dir(data, player_x, player_y);
    }
    else
        printf("Player is out of bounds for rendering.\n");
}
void render_miniplayer(t_data *data)
{
    int player_x;
    int player_y;
    int ofs_x;
    int ofs_y;
    int scale;

    scale = 4;
    ofs_x = 10;
    ofs_y = 10;
    player_x = ofs_x + (int)(data->player.x / scale);
    player_y = ofs_y + (int)(data->player.y / scale);
    draw_rectangle(
        &data->img,
        player_x - 2, // Small size for player
        player_y - 2,
        4,
        4,
        0xFF0000, // Red for player
        data->map.width * CELL_SIZE,
        data->map.height * CELL_SIZE
    );
    player_dir(data, player_x, player_y);
 }

void render_minimap(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            draw_rectangle(
                &data->img,
                10 + x * (CELL_SIZE / 4),
                10 + y * (CELL_SIZE / 4),
                CELL_SIZE / 4,
                CELL_SIZE / 4,
                color_cell_matching(data->map.grid[y][x]),
                data->map.width * CELL_SIZE,
                data->map.height * CELL_SIZE
            );
            x++;
        }
        y++;
    }
    render_miniplayer(data);
}

void render(t_data *data)
{
    clear_img(data);
    raycast(data);
    render_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
// void render(t_data *data)
// {
//     clear_img(data);
//     // raycast(data);
//     render_minimap(data);
//     // render_map(data);    // Draw the map
//     // render_player(data); // Draw the player
//     mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }





/*      Player movements & map & player rendering test      */

    // void render(t_data *data)
    // {
    //     clear_img(data);
    //     render_map(data);    // Draw the map
    //     render_player(data); // Draw the player
    //     mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
    // }



/*      Scaled player movements & map & player rendering for minimap test      */
    // void render(t_data *data)
    // {
    //     clear_img(data);
    //     render_minimap(data);
    //     mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
    // }