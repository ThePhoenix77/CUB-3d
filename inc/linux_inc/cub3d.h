/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:57:48 by aragragu          #+#    #+#             */
/*   Updated: 2024/12/21 13:57:51 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>



typedef struct s_data
{
    char    *file_data[6];
    char    **map;
    int     fd;
}               t_data;


void    my_perror(int status, char *str);
int	ft_strncmp(const char *s1, const char *s2, int n);
int ft_strlen(const char *str);
int	check_file(const char *argv);
void    file_parsing(t_data *data, char *str);

#endif