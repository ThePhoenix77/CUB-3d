/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:46:09 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/11 21:38:45 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"


void    load_gun_frames(t_data  *data)
{
    int     i;
    int     gun_num;

    i = 0;
    gun_num = 1;
    // exit(0);
    while (i < 8)
    {
        data->game.gun[i] = ft_malloc(sizeof(t_textures), ALLOC);
        if (!data->game.gun[i])
            my_perror(1, "error: malloc failed\n");
        data->game.gun[i]->image = mlx_xpm_file_to_image(data->mlx, ft_strjoin(ft_strjoin(ft_strdup("assets/gun_frames/gun_"), ft_itoa(gun_num)), ".xpm"), &data->game.gun[i]->width, &data->game.gun[i]->height);
    // printf("path : [%s]\n", ft_strjoin("assets/cs2/", ft_strjoin(ft_itoa(gun_num), ".xpm")));
        if (!data->game.gun[i]->image)
        {
            // free_textures(data);
            my_perror(1, "load textures::failed\n");
        }
        data->game.gun[i]->add = mlx_get_data_addr(data->game.gun[i]->image, &data->game.gun[i]->bp_pixels, &data->game.gun[i]->l_length, &data->game.gun[i]->endian);
        i++;
        gun_num++;
    }
    data->game.current_frame = 0;
    data->game.frame_delay = 4;
    data->game.frame_counter = 0;
}


static void update_gun_frame(t_game *game)
{
    if (game->frame_counter >= game->frame_delay)
    {
        game->current_frame = (game->current_frame + 1) % 8;
        game->frame_counter = 0;
    }
    game->frame_counter++;
}


static void draw_gun_pixel_row(t_data *data, t_textures *gun_frame, int j, int dest_y, int x)
{
    int i;
    int bpp_src = gun_frame->bp_pixels / 8;
    int bpp_dst = data->img.bpp / 8;
    
    char *src_row = gun_frame->add + j * gun_frame->l_length;
    unsigned char *dst_row = (unsigned char *)data->img.data + dest_y * data->img.size_line;

    i = 0;
    while (i < gun_frame->width)
    {
        int dest_x = x + i;
        if (dest_x >= 0 && dest_x < MAP_WIDTH)
        {
            int color = *(int *)(src_row + i * bpp_src);
            if (color != 0x000000)
                *(int *)(dst_row + dest_x * bpp_dst) = color;
        }
        i++;
    }
}

static void draw_gun_pixels(t_data *data, t_textures *gun_frame, int x, int y)
{
    int j;
    int dest_y;

    j = 0;
    while (j < gun_frame->height)
    {
        dest_y = y + j;
        if (dest_y >= 0 && dest_y < MAP_HEIGHT)
            draw_gun_pixel_row(data, gun_frame, j, dest_y, x);  // Pass `j` separately
        j++;
    }
}

void render_gun_sprite(t_data *data)
{
    t_textures  *gun_frame;
    int         x, y;

    update_gun_frame(&data->game);
    gun_frame = data->game.gun[data->game.current_frame];
    if (!gun_frame || !gun_frame->add)
        return;
    x = (MAP_WIDTH - gun_frame->width) / 2;
    y = MAP_HEIGHT - gun_frame->height + 10;
    draw_gun_pixels(data, gun_frame, x, y);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
