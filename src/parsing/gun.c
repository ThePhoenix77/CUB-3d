/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:46:09 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/08 21:42:47 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"


void print_gun_textures(t_textures *gun[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (gun[i] != NULL)
        {
            printf("[%d] image: %p, add: %p, width: %d, height: %d, bpp: %d, line_length: %d, endian: %d\n",
                i,
                gun[i]->image,
                gun[i]->add,
                gun[i]->width,
                gun[i]->height,
                gun[i]->bits_per_pixel,
                gun[i]->line_length,
                gun[i]->endian);
        }
        else
        {
            printf("[%d] NULL\n", i);
        }
    }
}

void    load_gun_frames(t_data  *data)
{
    int     i;
    int     gun_num;

    i = 0;
    gun_num = 0;
    // ft_strjoin(ft_strjoin(ft_strdup("assets/gun_frames/gun_"), ft_itoa(gun_num)), ".xpm")
    // exit(0);
    while (i < 43)
    {
        data->game.gun[i] = ft_malloc(sizeof(t_textures), ALLOC);
        if (!data->game.gun[i])
            my_perror(1, "error: malloc failed\n");
        data->game.gun[i]->image = mlx_xpm_file_to_image(data->mlx, ft_strjoin("assets/cs2/", ft_strjoin(ft_itoa(gun_num), ".xpm")), &data->game.gun[i]->width, &data->game.gun[i]->height);
    printf("path : [%s]\n", ft_strjoin("assets/cs2/", ft_strjoin(ft_itoa(gun_num), ".xpm")));
        if (!data->game.gun[i]->image)
        {
            // free_textures(data);
            my_perror(1, "load textures::failed\n");
        }
        data->game.gun[i]->add = mlx_get_data_addr(data->game.gun[i]->image, &data->game.gun[i]->bits_per_pixel, &data->game.gun[i]->line_length, &data->game.gun[i]->endian);
        i++;
        gun_num++;
    }
    data->game.current_frame = 0;
    data->game.frame_delay = 2;
    data->game.frame_counter = 0;
}


// void    render_gun_sprite(t_data *data)
// {
//     int x;
//     int y;
//     t_game *game;

//     if (data->game.frame_counter >= data->game.frame_delay) 
//     {
//         data->game.current_frame = (data->game.current_frame + 1) % 43;
//         data->game.frame_counter = 0;
//     }
//     data->game.frame_counter++;
//     game = &data->game;
//     x = (MAP_WIDTH - game->gun[game->current_frame]->width) / 2;
//     y = MAP_HEIGHT - game->gun[game->current_frame]->height;
//     mlx_put_image_to_window(data->mlx, data->win, game->gun[game->current_frame]->image, x, y);
// }
void render_gun_sprite(t_data *data)
{
    int         x, y;
    t_game      *game = &data->game;
    t_textures  *gun_frame;
    int         bytes_per_pixel_src, bytes_per_pixel_dst;
    int         i, j;
    char        *src_row;
    unsigned char *dst_row;

    if (game->frame_counter >= game->frame_delay)
    {
        game->current_frame = (game->current_frame + 1) % 43;
        game->frame_counter = 0;
    }
    game->frame_counter++;
    gun_frame = game->gun[game->current_frame];
    if (!gun_frame || !gun_frame->add)
        return;

    x = (MAP_WIDTH - gun_frame->width) / 2;
    y = MAP_HEIGHT - gun_frame->height;
    bytes_per_pixel_src = gun_frame->bits_per_pixel / 8;
    bytes_per_pixel_dst = data->img.bpp / 8;

    j = 0;
    while (j < gun_frame->height)
    {
        int dest_y = y + j;
        if (dest_y >= 0 && dest_y < MAP_HEIGHT)
        {
            dst_row = (unsigned char *)data->img.data + dest_y * data->img.size_line;
            src_row = gun_frame->add + j * gun_frame->line_length;
            i = 0;
            while (i < gun_frame->width)
            {
                int dest_x = x + i;
                if (dest_x >= 0 && dest_x < MAP_WIDTH)
                {
                    int color = *(int *)(src_row + i * bytes_per_pixel_src);
                    if (color != 0x000000)
                    {
                        *(int *)(dst_row + dest_x * bytes_per_pixel_dst) = color;
                    }
                }
                i++;
            }
        }
        j++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

