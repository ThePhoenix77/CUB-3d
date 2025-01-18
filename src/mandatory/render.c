#include "cub3d.h"

int bound_check(t_data *data, int player_x, int player_y)
{
    return (player_x >= 0 && player_x < data->map.width * 32 &&
        player_y >= 0 && player_y < data->map.height * 32);
}
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
        draw_rectangle(&data->img, dot_x - 1, dot_y - 1, 2, 2, color, data->map.width * CELL_SIZE, data->map.height * CELL_SIZE);
        i++;
    }
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
void calculate_viewport(t_data *data, int *start_x, int *start_y, int *end_x, int *end_y)
{
    int player_x = (int)(data->player.x / CELL_SIZE);
    int player_y = (int)(data->player.y / CELL_SIZE);
    *start_x = player_x - (MINIMAP_WIDTH / (2 * (CELL_SIZE / MINIMAP_SCALE)));
    *start_y = player_y - (MINIMAP_HEIGHT / (2 * (CELL_SIZE / MINIMAP_SCALE)));
    *end_x = player_x + (MINIMAP_WIDTH / (2 * (CELL_SIZE / MINIMAP_SCALE)));
    *end_y = player_y + (MINIMAP_HEIGHT / (2 * (CELL_SIZE / MINIMAP_SCALE)));
}

void draw_minimap_tiles(t_data *data, int start_x, int start_y, int end_x, int end_y)
{
    int y = start_y;
    while (y <= end_y)
    {
        int x = start_x;
        while (x <= end_x)
        {
            if (x >= 0 && y >= 0 && x < data->map.width && y < data->map.height)
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
    int player_minimap_x = (MINIMAP_WIDTH / 2) - 2;
    int player_minimap_y = (MINIMAP_HEIGHT / 2) - 2;
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
    frame_color = 0xFFD700; // Golden color
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
    int viewport_start_x, viewport_start_y, viewport_end_x, viewport_end_y;

    calculate_viewport(data, &viewport_start_x, &viewport_start_y, &viewport_end_x, &viewport_end_y);
    draw_minimap_frame(data);
    draw_minimap_tiles(data, viewport_start_x, viewport_start_y, viewport_end_x, viewport_end_y);
    draw_player_on_minimap(data);
}

void render(t_data *data)
{
    clear_img(data);
    raycast(data);
    render_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

// void player_dir(t_data *data, int player_x, int player_y)
// {
//     int x_end_forward;
//     int y_end_forward;
//     int x_end_backward;
//     int y_end_backward;

//     x_end_forward = player_x + (int)(data->player.dir_x * CELL_SIZE / 1.5);
//     y_end_forward = player_y + (int)(data->player.dir_y * CELL_SIZE / 1.5);
//     x_end_backward = player_x - (int)(data->player.dir_x * CELL_SIZE / 1.5);
//     y_end_backward = player_y - (int)(data->player.dir_y * CELL_SIZE / 1.5);
//     draw_line(&data->img, player_x, player_y, x_end_forward, y_end_forward, 0x00FF00);
//     draw_line(&data->img, player_x, player_y, x_end_backward, y_end_backward, 0x00FF00);
//     draw_rectangle(&data->img, x_end_forward - 1, y_end_forward - 1, 2, 2, 0x0000FF, data->map.width * CELL_SIZE, data->map.height * CELL_SIZE);
//     draw_rectangle(&data->img, x_end_backward - 1, y_end_backward - 1, 2, 2, 0x0000FF, data->map.width * CELL_SIZE, data->map.height * CELL_SIZE);
// }

// void render_minimap(t_data *data)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < data->map.height)
//     {
//         x = 0;
//         while (x < data->map.width)
//         {
//             draw_rectangle(
//                 &data->img,
//                 10 + x * (CELL_SIZE / 4),
//                 10 + y * (CELL_SIZE / 4),
//                 CELL_SIZE / 4,
//                 CELL_SIZE / 4,
//                 color_cell_matching(data->map.grid[y][x]),
//                 data->map.width * CELL_SIZE,
//                 data->map.height * CELL_SIZE
//             );
//             x++;
//         }
//         y++;
//     }
//     render_miniplayer(data);
// }




// default map and player rendering for testing

/*void render_player(t_data *data)
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
}*/

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

/*      Circular minimap    */

// int is_within_circle(int center_x, int center_y, int x, int y, int radius)
// {
//     int dx = x - center_x;
//     int dy = y - center_y;
//     return (dx * dx + dy * dy) <= (radius * radius);
// }

// // Helper to convert degrees to radians
// float deg_to_rad(float angle)
// {
//     return angle * (PI / 180.0f);
// }

// // Rotate a point (x, y) around the center by an angle in radians
// void rotate_point(int *x, int *y, int center_x, int center_y, float angle)
// {
//     int dx = *x - center_x;
//     int dy = *y - center_y;

//     float rotated_x = dx * cos(angle) - dy * sin(angle);
//     float rotated_y = dx * sin(angle) + dy * cos(angle);

//     *x = center_x + (int)rotated_x;
//     *y = center_y + (int)rotated_y;
// }

// // Put a pixel on the image
// void put_pixel(t_img *img, int x, int y, int color)
// {
//     if (x >= 0 && x < img->width && y >= 0 && y < img->height)
//     {
//         int pixel_index = (y * img->size_line) + (x * (img->bpp / 8));
//         img->data[pixel_index] = (color & 0xFF);           // Blue
//         img->data[pixel_index + 1] = (color >> 8) & 0xFF;  // Green
//         img->data[pixel_index + 2] = (color >> 16) & 0xFF; // Red
//         if (img->bpp == 32)
//             img->data[pixel_index + 3] = (color >> 24) & 0xFF; // Alpha
//     }
// }

// // Draw a filled circle
// void draw_circle(t_img *img, int center_x, int center_y, int radius, int color)
// {
//     for (int y = -radius; y <= radius; y++)
//     {
//         for (int x = -radius; x <= radius; x++)
//         {
//             if (is_within_circle(center_x, center_y, center_x + x, center_y + y, radius))
//                 put_pixel(img, center_x + x, center_y + y, color);
//         }
//     }
// }

// void add_to_trail(t_player_trail *trail, int x, int y)
// {
//     // Shift trail positions to make space for new one
//     for (int i = TRAIL_MAX_SIZE - 1; i >= 0; i--)
//     {
//         trail->x[i] = trail->x[i - 1];
//         trail->y[i] = trail->y[i - 1];
//     }

//     // Add the new position to the front
//     trail->x[0] = x;
//     trail->y[0] = y;

//     // If we haven't filled the trail yet, increase the size
//     if (trail->size < TRAIL_MAX_SIZE)
//         trail->size++;
// }

// void render_gta_minimap(t_data *data)
// {
//     int center_x = MINIMAP_CENTER_X; // Center of the minimap
//     int center_y = MINIMAP_CENTER_Y;
//     int radius = MINIMAP_RADIUS;    // Radius of the circular minimap
//     int tile_size = MINIMAP_TILE_SIZE; // Scale for the minimap tiles

//     // Draw the circular minimap background
//     // for (int y = -radius; y <= radius; y++)
//     // {
//     //     for (int x = -radius; x <= radius; x++)
//     //     {
//     //         if (x * x + y * y <= radius * radius) // Check if the point is within the circle
//     //         {
//     //             int px = center_x + x;
//     //             int py = center_y + y;
//     //             draw_pixel(&data->img, px, py, 0x222222); // Dark gray background
//     //         }
//     //     }
//     // }

//     // Draw the minimap cells
//     for (int map_y = 0; map_y < data->map.height; map_y++)
//     {
//         for (int map_x = 0; map_x < data->map.width; map_x++)
//         {
//             // Calculate the screen position for the current map cell
//             int screen_x = center_x + (map_x - (int)data->player.x) * tile_size;
//             int screen_y = center_y + (map_y - (int)data->player.y) * tile_size;

//             // Check if the cell is within the circular minimap boundaries
//             int dx = screen_x - center_x;
//             int dy = screen_y - center_y;
//             if (dx * dx + dy * dy <= radius * radius)
//             {
//                 int color = color_cell_matching(data->map.grid[map_y][map_x]);
//                 draw_rectangle(
//                     &data->img,
//                     screen_x - tile_size / 2,
//                     screen_y - tile_size / 2,
//                     tile_size,
//                     tile_size,
//                     color,
//                     data->img.width,
//                     data->img.height
//                 );
//             }
//         }
//     }

//     // Draw the player as a small rectangle
//     draw_rectangle(
//         &data->img,
//         center_x - tile_size / 4,
//         center_y - tile_size / 4,
//         tile_size / 2,
//         tile_size / 2,
//         0x00FF00, // Green (player color)
//         data->img.width,
//         data->img.height
//     );

//     // Draw the player direction line
//     // double player_angle = atan2(data->player.dir_y, data->player.dir_x);
//     int line_length = tile_size * 3;
//     int line_x = center_x + (int)(data->player.dir_x * line_length);
//     int line_y = center_y + (int)(data->player.dir_y * line_length);
//     draw_line(&data->img, center_x, center_y, line_x, line_y, 0xFF0000); // Red line
// }






// Render the GTA-style minimap with zoomed-out effect
// void render_gta_minimap(t_data *data)
// {
//     int minimap_radius = MINIMAP_RADIUS;
//     int center_x = minimap_radius; // Center of the minimap in pixels
//     int center_y = minimap_radius;
    
//     // Decrease the scale for a zoomed-out effect (for example, increasing MINIMAP_SCALE)
//     int tile_size = CELL_SIZE / (MINIMAP_SCALE * 1.5); // Smaller tiles = more zoomed out

//     // Player's position and direction vector
//     int player_x = (int)(data->player.x / CELL_SIZE);
//     int player_y = (int)(data->player.y / CELL_SIZE);
//     float player_angle = atan2(data->player.dir_y, data->player.dir_x); // Player's angle in radians

//     // Optionally, draw the minimap border last
//     draw_circle(&data->img, center_x, center_y, minimap_radius + 10, 0xFFFFFF);
//     draw_circle(&data->img, center_x, center_y, minimap_radius, 0x000000);

//     // Loop through visible map tiles
//     for (int y = -minimap_radius; y <= minimap_radius; y++)
//     {
//         for (int x = -minimap_radius; x <= minimap_radius; x++)
//         {
//             // Calculate the relative map coordinates
//             int map_x = player_x + (x / tile_size);
//             int map_y = player_y + (y / tile_size);

//             // Check if the tile is within map bounds
//             if (map_x < 0 || map_x >= data->map.width || map_y < 0 || map_y >= data->map.height)
//                 continue;

//             // Get the color for the current map tile
//             int color = color_cell_matching(data->map.grid[map_y][map_x]);

//             // Calculate the tile's position on the screen relative to the player
//             int tile_screen_x = center_x + x * tile_size;
//             int tile_screen_y = center_y + y * tile_size;

//             // Rotate the tile screen position based on the player's angle
//             rotate_point(&tile_screen_x, &tile_screen_y, center_x, center_y, -player_angle);

//             // Only render tiles within the circular region of the minimap
//             if (is_within_circle(center_x, center_y, tile_screen_x, tile_screen_y, minimap_radius))
//             {
//                 draw_rectangle(&data->img, tile_screen_x, tile_screen_y, tile_size, tile_size, color, data->img.width, data->img.height);
//             }
//         }
//     }

//     // Draw the player as a small purple dot at the center of the minimap
//     draw_rectangle(&data->img, center_x - 2, center_y - 2, 4, 4, 0xFF00FF, data->img.width, data->img.height); // Purple dot for player

//     // Determine the direction of the trail based on the player's first facing direction
//     float trail_angle = player_angle;  // Start with the player's initial angle
//     float prev_angle = player_angle;   // Keep track of the previous angle
//     int step_x = 0, step_y = 0;

//     // Adjust angle smoothly
//     float angle_diff = trail_angle - prev_angle;

//     // Normalize angle to be within [-PI, PI]
//     if (angle_diff > M_PI)
//         angle_diff -= 2 * M_PI;
//     else if (angle_diff < -M_PI)
//         angle_diff += 2 * M_PI;

//     // Interpolate smoothly toward the player's current direction (a simple smoothing factor)
//     float smoothing_factor = 0.1f;  // Adjust the smoothing factor as needed (lower = smoother)
//     trail_angle = prev_angle + angle_diff * smoothing_factor;

//     // Use step_x and step_y to represent the direction in which the trail moves
//     if (trail_angle >= -M_PI_4 && trail_angle < M_PI_4) {
//         step_y = 1; // East
//     } else if (trail_angle >= M_PI_4 && trail_angle < 3 * M_PI_4) {
//         step_y = -1; // North
//     } else if (trail_angle >= -3 * M_PI_4 && trail_angle < -M_PI_4) {
//         step_x = 1; // South
//     } else {
//         step_x = -1; // West
//     }

//     // Now smooth the trail by moving along the player's facing direction
//     int num_points = 10; // Number of fading points to draw
//     float offset_x = 0.0f, offset_y = 0.0f;  // Initial offset for smooth transition

//     // Smoothly shift the points over time
//     for (int i = 0; i < num_points; i++)
//     {
//         // Incrementally move along the direction the player is facing
//         offset_x += step_x * 0.2f;  // Small increment for smooth movement
//         offset_y += step_y * 0.2f;

//         // Calculate the screen position for each point in the trail
//         int trail_x = center_x + (int)(offset_x * tile_size);
//         int trail_y = center_y + (int)(offset_y * tile_size);
        
//         // Gradually decrease the intensity (fading effect)
//         int alpha = (255 * (num_points - i)) / num_points; // Fade out as i increases
//         int faded_color = (alpha << 24) | 0xFF0000; // Fading red (alpha + red color)

//         // Draw each fading point in the trail
//         draw_pixel(&data->img, trail_x, trail_y, faded_color);
//     }

//     // Update the previous angle for the next frame
//     prev_angle = trail_angle;
// }

// void render(t_data *data)
// {
//     clear_img(data);
//     raycast(data);

//     // Pass the player trail to the render_gta_minimap function
//     render_gta_minimap(data, &data->player_trail);

//     mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }