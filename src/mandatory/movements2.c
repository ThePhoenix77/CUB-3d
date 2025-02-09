# include "../../inc/linux_inc/cub3d.h"

// Helper function to check if a position is walkable
int is_walkable(t_map *map, double x, double y)
{
    // Calculate the grid cell boundaries the player hitbox should consider
    int top_left_x;
    int top_left_y;
    int bottom_right_x;
    int bottom_right_y;
    int walkable;

    top_left_x = (int)(x - HITBOX_MARG);
    top_left_y = (int)(y - HITBOX_MARG);
    bottom_right_x = (int)(x + HITBOX_MARG);
    bottom_right_y = (int)(y + HITBOX_MARG);
    walkable = (map->grid[top_left_y][top_left_x] == '0' ||
                    map->grid[top_left_y][top_left_x] == 'D') &&
                   (map->grid[top_left_y][bottom_right_x] == '0' ||
                    map->grid[top_left_y][bottom_right_x] == 'D') &&
                   (map->grid[bottom_right_y][top_left_x] == '0' ||
                    map->grid[bottom_right_y][top_left_x] == 'D') &&
                   (map->grid[bottom_right_y][bottom_right_x] == '0' ||
                    map->grid[bottom_right_y][bottom_right_x] == 'D');

    return (walkable);
}

void rotate_left(t_player *player)
{
    double old_dir_x;
    double old_plane_x;
    double cos_angle;
    double sin_angle;

    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;
    cos_angle = cos(-player->rot_speed);
    sin_angle = sin(-player->rot_speed);
    player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
    player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
    player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
    player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

void rotate_right(t_player *player)
{
    double old_dir_x;
    double old_plane_x;
    double cos_angle;
    double sin_angle;

    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;
    cos_angle = cos(player->rot_speed);
    sin_angle = sin(player->rot_speed);
    player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
    player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
    player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
    player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

/*

void normalize_vector(double *x, double *y)
{
    double magnitude = sqrt((*x) * (*x) + (*y) * (*y));
    if (magnitude > 0.0)
    {
        *x /= magnitude;
        *y /= magnitude;
    }
}

void rotate_left(t_player *player)
{
    double old_dir_x = player->dir_x;
    double old_plane_x = player->plane_x;
    double cos_angle = cos(-player->rot_speed);
    double sin_angle = sin(-player->rot_speed);

    player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
    player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
    player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
    player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;

    // Normalize direction vectors to prevent drift
    normalize_vector(&player->dir_x, &player->dir_y);
    normalize_vector(&player->plane_x, &player->plane_y);
}

void rotate_right(t_player *player)
{
    double old_dir_x = player->dir_x;
    double old_plane_x = player->plane_x;
    double cos_angle = cos(player->rot_speed);
    double sin_angle = sin(player->rot_speed);

    player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
    player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
    player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
    player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;

    // Normalize direction vectors to prevent drift
    normalize_vector(&player->dir_x, &player->dir_y);
    normalize_vector(&player->plane_x, &player->plane_y);
}

*/
