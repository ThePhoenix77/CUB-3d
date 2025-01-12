# include "cub3d.h"

// /home/tboussad/work/CUB-3d/maps/test.map

void ppos(t_player *player)
{
    printf("Player Position: x = %.2f, y = %.2f\n", player->x, player->y);
}

int handle_exit()
{
    // (void)param;
    printf("Exiting the program...\n");
    exit(0);
}

// void print_player_info(t_player *player)
// {
//     printf("Player Information:\n");
//     printf("-------------------\n");
//     printf("Position: (x: %.2f, y: %.2f)\n", player->x, player->y);
//     printf("Direction: (dir_x: %.2f, dir_y: %.2f)\n", player->dir_x, player->dir_y);
//     printf("Camera Plane: (plane_x: %.2f, plane_y: %.2f)\n", player->plane_x, player->plane_y);
//     printf("Movement Flags:\n");
//     printf("  Forward: %d\n", player->forward);
//     printf("  Backward: %d\n", player->backward);
//     printf("  Left: %d\n", player->left);
//     printf("  Right: %d\n", player->right);
//     printf("Rotation Flags:\n");
//     printf("  Rotate Left: %d\n", player->rotate_left);
//     printf("  Rotate Right: %d\n", player->rotate_right);
//     printf("Speeds:\n");
//     printf("  Move Speed: %.2f\n", player->move_speed);
//     printf("  Rotation Speed: %.2f\n", player->rot_speed);
//     printf("-------------------\n");
// }


int main()
{
    t_data data;

    data_init(&data);
    printf("Map Dimensions: Width = %d, Height = %d\n", data.map.width, data.map.height);

    mlx_hook(data.win, 2, 1L << 0, key_press, &data);
    mlx_hook(data.win, 3, 1L << 1, key_release, &data);
    mlx_loop_hook(data.mlx, game_loop, &data);
    mlx_hook(data.win, 17, 0, handle_exit, NULL);

    // print_player_info(&data.player);
    mlx_loop(data.mlx);

    return 0;
}
