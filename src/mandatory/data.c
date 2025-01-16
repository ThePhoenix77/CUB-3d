#include "cub3d.h"
#include <string.h>

void init_player_defaults(t_player *player)
{
    player->forward = 0;
    player->backward = 0;
    player->left = 0;
    player->right = 0;
    player->rotate_left = 0;
    player->rotate_right = 0;
    player->move_speed = MOVE_SPEED;
    player->rot_speed = 0.03;
}

void player_init(t_map *map, t_player *player)
{
    if (!find_player_position(map, player))
        quit("error: Player not found in the map !");
    init_player_defaults(player);
    // set_player_plane(player);
    // init_player_direction(player, map->grid[(int)player->y][(int)player->x]);
    init_player_direction(player, map->grid[(int)player->y / CELL_SIZE][(int)player->x / CELL_SIZE]);
}

// void img_init(t_data *data)
// {
//     data->img.img_ptr = mlx_new_image(data->mlx, data->map.width * 32, data->map.height * 32);
//     data->img.data = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.size_line, &data->img.endian);
// }

void init_img(t_data *data)
{
    data->img.width = data->map.width * CELL_SIZE;
    data->img.height = data->map.height * CELL_SIZE;

    data->img.img_ptr = mlx_new_image(data->mlx, data->img.width, data->img.height);
    if (!data->img.img_ptr)
        quit("Error: Image creation failed!");

    data->img.data = (unsigned char *)mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.size_line, &data->img.endian);
    if (!data->img.data)
        quit("Error: Failed to get image data address!");
}



// void print_map(t_data *data) {
//     for (int y = 0; y < data->map.height; y++) {
//         if (data->map.grid[y] != NULL) {
//             printf("%s\n", data->map.grid[y]);
//         } else {
//             printf("Null string at row %d\n", y);
//         }
//     }
// }

// void max_dimensions(t_data *data)
// {
//     data->screen_width = 800;
//     data->screen_height = 600;
//     data->screen_width = data->map.width * CELL_SIZE;
//     data->screen_height = data->map.height * CELL_SIZE;

//     if (data->screen_width > MAX_SCREEN_WIDTH)
//         data->screen_width = MAX_SCREEN_WIDTH;
//     if (data->screen_height > MAX_SCREEN_HEIGHT)
//         data->screen_height = MAX_SCREEN_HEIGHT;
// }

void data_init(t_data *data)
{
    // Initialize MiniLibX
    data->mlx = mlx_init();
    if (!data->mlx)
        quit("Error: MiniLibX initialization failed!");

    // Initialize the map
    map_init(&data->map, "/home/tboussad/work/CUB-3d/maps/test.map");
    if (data->map.grid == NULL)
        quit("Error: Map initialization failed!");

    // Create a new window
    data->win = mlx_new_window(data->mlx, data->map.width * CELL_SIZE, data->map.height * CELL_SIZE, "Cub3D");
    if (!data->win)
        quit("Error: Window creation failed!");

    // Initialize the player
    player_init(&data->map, &data->player);

    // Initialize the image
    init_img(data);
}




// void data_init(t_data *data)
// {
//     data->mlx = mlx_init();
//     if (!data->mlx)
//         quit("error: MiniLibX initialization has failed !");
//     // else printf("mlx init done !\n");

//     // print_map(data);
//     // printf("width: %d and height: %d\n", data->map.width, data->map.height);
    
//     map_init(&data->map, "/home/tboussad/work/CUB-3d/maps/test.map");
//     if (data->map.grid == NULL)
//         quit("error: Map initialization has failed !");
//     data->win = mlx_new_window(data->mlx, data->map.width * CELL_SIZE, data->map.height * CELL_SIZE, "Cub3D");
//     if (!data->win)
//         quit("error: Window creation has failed !");
//     else printf("mlx win done !\n");
//     player_init(&data->map, &data->player);

//     // Initialize the image for rendering, setting the proper width and height for the image
//     data->img.img_ptr = mlx_new_image(data->mlx, data->map.width * CELL_SIZE, data->map.height * CELL_SIZE);
//     if (!data->img.img_ptr)
//         quit("error: Image creation has failed !");
    
//     // Get the pixel data from the image
//     data->img.data = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.size_line, &data->img.endian);
//     if (!data->img.data)
//         quit("error: Failed to get image data address !");
// }
