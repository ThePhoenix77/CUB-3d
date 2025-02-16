/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:52:59 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/16 15:44:00 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int	game_loop(t_data *data)
{
	render(data);
	move_player(data);
	return (0);
}
