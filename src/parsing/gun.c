/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:46:09 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/08 21:11:05 by aragragu         ###   ########.fr       */
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
        // data->game.gun[i]->add = mlx_get_data_addr(data->game.gun[i]->image, &data->game.gun[i]->bits_per_pixel, &data->game.gun[i]->line_length, &data->game.gun[i]->endian);
        i++;
        gun_num++;
    }
    data->game.current_frame = 0;
    data->game.frame_delay = 5;
    data->game.frame_counter = 0;
}


void    render_gun_sprite(t_data *data)
{
    int x;
    int y;
    t_game *game;

    if (data->game.frame_counter >= data->game.frame_delay) 
    {
        data->game.current_frame = (data->game.current_frame + 1) % 43;
        data->game.frame_counter = 0;
    }
    data->game.frame_counter++;
    game = &data->game;
    x = (MAP_WIDTH - game->gun[game->current_frame]->width) / 2;
    y = MAP_HEIGHT - game->gun[game->current_frame]->height;
    mlx_put_image_to_window(data->mlx, data->win, game->gun[game->current_frame]->image, x, y);
}
