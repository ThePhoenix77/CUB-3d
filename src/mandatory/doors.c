# include "../../inc/linux_inc/cub3d.h"

// void open_door(t_data *data)
// {
//     double ray_x = data->player.x;
//     double ray_y = data->player.y;
//     double step_size = 0.1; // Small step size for precision
//     double max_distance = 3.0; // Max distance the player can open a door

//     while (max_distance > 0)
//     {
//         ray_x += data->player.dir_x * step_size;
//         ray_y += data->player.dir_y * step_size;
//         max_distance -= step_size;

//         int map_x = (int)(ray_x);
//         int map_y = (int)(ray_y);

//         if (data->map.grid[map_y][map_x] == '1') // Hit a wall
//             return; // Stop checking

//         if (data->map.grid[map_y][map_x] == 'D') // Hit a door
//         {
//             // Toggle door state
//             data->map.grid[map_y][map_x] = (data->map.doors[map_y][map_x]) ? 'D' : '0';
//             data->map.doors[map_y][map_x] = !data->map.doors[map_y][map_x];

//             // Re-render the scene
//             render(data);

//             printf("Door toggled at (%d, %d)\n", map_x, map_y);
//             return;
//         }
//     }
// }

// void cast_ray_for_door(t_data *data)
// {
//     double ray_x = data->player.x;
//     double ray_y = data->player.y;
//     double step_size = 0.1; // Small step size for precision
//     double max_distance = 3.0; // Max distance the player can open a door

//     while (max_distance > 0)
//     {
//         ray_x += data->player.dir_x * step_size;
//         ray_y += data->player.dir_y * step_size;
//         max_distance -= step_size;

//         int map_x = (int)(ray_x);
//         int map_y = (int)(ray_y);

//         if (data->map.grid[map_y][map_x] == '1') // Hit a wall
//             return; // Stop checking

//         if (data->map.grid[map_y][map_x] == 'D') // Hit a door
//         {
//             // Toggle door state
//             data->map.grid[map_y][map_x] = (data->map.doors[map_y][map_x]) ? 'D' : '0';
//             data->map.doors[map_y][map_x] = !data->map.doors[map_y][map_x];

//             // Force a redraw so the door disappears/appears
//             mlx_clear_window(data->mlx, data->win);
//             draw_map(data);

//             printf("Door toggled at (%d, %d)\n", map_x, map_y);
//             return;
//         }
//     }
// }


// void draw_map(t_data *data)
// {
//     for (int y = 0; y < MAP_HEIGHT; y++)
//     {
//         for (int x = 0; x < MAP_WIDTH; x++)
//         {
//             if (data->map.grid[y][x] == '1')
//                 draw_wall(x, y);
//             else if (data->map.grid[y][x] == 'D')
//                 draw_door(x, y);
//             else
//                 draw_floor(x, y); // Walkable space
//         }
//     }
// }
