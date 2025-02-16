/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:00:02 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/12 20:03:12 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	handle_key_press(int key, t_data *data)
{
	if (key == W_KEY)
		data->player.forward = 1;
	else if (key == S_KEY)
		data->player.backward = 1;
	else if (key == A_KEY)
		data->player.left = 1;
	else if (key == D_KEY)
		data->player.right = 1;
}

void	handle_key_press_rotation(int key, t_data *data)
{
	if (key == LEFT_KEY)
		data->player.rotate_left = 1;
	else if (key == RIGHT_KEY)
		data->player.rotate_right = 1;
	else if (key == ESCAPE_KEY)
		quit("Game exited successfully.");
}

void	handle_key_release(int key, t_data *data)
{
	if (key == W_KEY)
		data->player.forward = 0;
	else if (key == S_KEY)
		data->player.backward = 0;
	else if (key == A_KEY)
		data->player.left = 0;
	else if (key == D_KEY)
		data->player.right = 0;
}

void	handle_key_release_rotation(int key, t_data *data)
{
	if (key == LEFT_KEY)
		data->player.rotate_left = 0;
	else if (key == RIGHT_KEY)
		data->player.rotate_right = 0;
}
