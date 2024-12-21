/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:57:31 by aragragu          #+#    #+#             */
/*   Updated: 2024/12/21 17:59:21 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/linux_inc/cub3d.h"

int main(int argc, char *argv[])
{
	t_data  *data;

	if (argc == 2)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			my_perror(1, "malloc error\n");
		file_parsing(data, argv[1]);
		puts("done");
	}
	else
		my_perror(1, "wrong arguments\n");
}