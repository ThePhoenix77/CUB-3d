# include "cub3d.h"

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
