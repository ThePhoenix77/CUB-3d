/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:58:49 by aragragu          #+#    #+#             */
/*   Updated: 2024/12/21 18:01:04 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/linux_inc/cub3d.h"

void	my_perror(int status, char *str)
{
	write(2, str, ft_strlen(str));
	exit(status);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_file(const char *argv)
{
	int		fd;
	int		lenght;
	char	*path;

	fd = 0;
	lenght = ft_strlen(argv);
	if (lenght >= 4 && !ft_strncmp(&argv[lenght - 4], ".cub", 4))
	{
		path = (char *)(argv);
		fd = open(path, O_RDONLY);
		if (fd == -1)
			my_perror(1, "Error: Can't open map file\n");
	}
	else
		my_perror(1, "Error: Wrong map file extension\n");
	return (fd);
}

char	*read_map(int fd)
{
	char	*line;
	char	*whole_map;
	char	*tmp;

	line = get_next_line(fd);
	whole_map = ft_strdup("");
	while (line)
	{
		tmp = whole_map;
		whole_map = ft_strjoin(whole_map, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (whole_map);
}


void print_2d_array(char **array) {
    if (!array) {
        printf("Array is NULL\n");
        return;
    }

    for (int i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}


char	**store_data(int fd)
{
	char	**str;
	char	*line;

	line =	read_map(fd);
	str = ft_split(line, '\n');
	print_2d_array(str);
	return (str);
}

void	file_parsing(t_data *data, char *str)
{
	data->fd = check_file(str);
	data->file_data = store_data(data->fd);
}