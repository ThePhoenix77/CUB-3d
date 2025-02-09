# include "cub3d.h"

// int key_press(int key, t_data *data)
// {
//     if (key == W_KEY)
//         data->player.forward = 1;
//     if (key == S_KEY)
//         data->player.backward = 1;
//     if (key == A_KEY)
//         data->player.left = 1;
//     if (key == D_KEY)
//         data->player.right = 1;
//     if (key == LEFT_KEY)
//         data->player.rotate_left = 1;
//     if (key == RIGHT_KEY)
//         data->player.rotate_right = 1;
//     if (key == ESCAPE_KEY)
//         quit("Game exited successfully!");
//     return (0);
// }

// int key_release(int key, t_data *data)
// {
//     if (key == W_KEY)
//         data->player.forward = 0;
//     if (key == S_KEY)
//         data->player.backward = 0;
//     if (key == A_KEY)
//         data->player.left = 0;
//     if (key == D_KEY)
//         data->player.right = 0;
//     if (key == LEFT_KEY)
//         data->player.rotate_left = 0;
//     if (key == RIGHT_KEY)
//         data->player.rotate_right = 0;
//     return (0);
// }

// void toggle_door(t_map *map, int player_x, int player_y)
// {
//     int grid_x = player_x / CELL_SIZE;
//     int grid_y = player_y / CELL_SIZE;

//     if (map->grid[grid_y][grid_x] == 'D')
//     {
//         // Toggle door state (0 = closed, 1 = open)
//         map->doors[grid_y][grid_x] = !map->doors[grid_y][grid_x];
//     }
// }

// void toggle_door(t_map *map, int player_x, int player_y)
// {
//     int grid_x = player_x / CELL_SIZE;
//     int grid_y = player_y / CELL_SIZE;
//     printf("Before toggle: %d\n", map->doors[grid_y][grid_x]);

//     if (map->grid[grid_y][grid_x] == 'D') // Ensure the player is in front of a door
//     {
//         if (map->doors[grid_y][grid_x] == 0)
//             map->doors[grid_y][grid_x] = 1; // Open the door
//         else
//             map->doors[grid_y][grid_x] = 0; // Close the door

//         printf("Door at (%d, %d) is now %s\n", grid_x, grid_y, map->doors[grid_y][grid_x] ? "OPEN" : "CLOSED");
//     }
//     printf("After toggle: %d\n", map->doors[grid_y][grid_x]);
// }
// void toggle_door(t_map *map, int player_x, int player_y)
// {
//     int grid_x = player_x / CELL_SIZE;
//     int grid_y = player_y / CELL_SIZE;

//     // Loop through adjacent tiles
//     for (int dy = -1; dy <= 1; dy++)
//     {
//         for (int dx = -1; dx <= 1; dx++)
//         {
//             if (dx == 0 && dy == 0) 
//                 continue; // Skip player's position
            
//             int nx = grid_x + dx;
//             int ny = grid_y + dy;

//             // Ensure within bounds
//             if (nx >= 0 && ny >= 0 && nx < MAP_WIDTH && ny < MAP_HEIGHT)
//             {
//                 if (map->grid[ny][nx] == 'D')  // Found a door
//                 {
//                     // Toggle door state
//                     map->doors[ny][nx] = !map->doors[ny][nx];  
//                     printf("Door at (%d, %d) is now %s\n", nx, ny, map->doors[ny][nx] ? "OPEN" : "CLOSED");
//                     return; // Stop after toggling one door
//                 }
//             }
//         }
//     }
// }

int key_press(int key, t_data *data)
{
    if (key == W_KEY)
    {
        data->player.forward = 1;
        printf("Key Pressed: W (Forward)\n");
    }
    else if (key == S_KEY)
    {
        data->player.backward = 1;
        printf("Key Pressed: S (Backward)\n");
    }
    else if (key == A_KEY)
    {
        data->player.left = 1;
        printf("Key Pressed: A (Strafe Left)\n");
    }
    else if (key == D_KEY)
    {
        data->player.right = 1;
        printf("Key Pressed: D (Strafe Right)\n");
    }
    // else if (key == O_KEY)
    // {
    //     // open_door(data);
    //     toggle_door(&data->map, data->player.x, data->player.y);
    //     printf("Key Pressed: O (Attempting to Open/Close Door)\n");
    // }
    else if (key == LEFT_KEY)
    {
        data->player.rotate_left = 1;
        printf("Key Pressed: Left Arrow (Rotate Left)\n");
    }
    else if (key == RIGHT_KEY)
    {
        data->player.rotate_right = 1;
        printf("Key Pressed: Right Arrow (Rotate Right)\n");
    }
    else if (key == ESCAPE_KEY)
    {
        printf("Key Pressed: Escape (Quit Game)\n");
        quit("Game exited successfully.");
    }
    else
        printf("Key Pressed: Unknown Key (key: %d)\n", key);
    // clear_img(data);
    return (0);
}

int key_release(int key, t_data *data)
{
    if (key == W_KEY)
    {
        data->player.forward = 0;
        printf("Key Released: W (Forward)\n");
    }
    else if (key == S_KEY)
    {
        data->player.backward = 0;
        printf("Key Released: S (Backward)\n");
    }
    else if (key == A_KEY)
    {
        data->player.left = 0;
        printf("Key Released: A (Strafe Left)\n");
    }
    else if (key == D_KEY)
    {
        data->player.right = 0;
        printf("Key Released: D (Strafe Right)\n");
    }
    else if (key == LEFT_KEY)
    {
        data->player.rotate_left = 0;
        printf("Key Released: Left Arrow (Rotate Left)\n");
    }
    else if (key == RIGHT_KEY)
    {
        data->player.rotate_right = 0;
        printf("Key Released: Right Arrow (Rotate Right)\n");
    }
    else
        printf("Key Released: Unknown Key (key: %d)\n", key);
    // clear_img(data);
    return (0);
}

