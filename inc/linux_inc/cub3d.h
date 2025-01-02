/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:51:35 by aragragu          #+#    #+#             */
/*   Updated: 2024/12/31 21:11:03 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif


typedef struct s_textures
{
	char	*norh;
	char	*west;
	char	*east;
	char	*south;
	char	*floor;
	char	*ceiling;
}			t_textures;

typedef struct s_parsing
{
	int			fd;
	int			file_lenght;
	int			map_start_index;
	char		**file_lines;
}				t_parsing;


typedef struct s_data
{
	t_textures  textures;
	t_parsing	*info;
	char		**map;
	int	 fd;
}				t_data;


void	my_perror(int status, char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
int	 	ft_strlen(const char *str);
int		check_file(const char *argv);
void	file_parsing(t_data *data, char *str);
void	store_data(t_data *data, int fd);
char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	fill_texture(char *str, char **texture, int *count);
int		file_lenght(char *str);
void	get_file_lines(char *str, t_parsing *info);
int		map_first_line_index(char **str);
void	parse_map(t_data *data);
void	fill_ceiling(char *str, char **texture, int *count);
void	fill_floor(char *str, char **texture, int *count);
void	check_rest(char	*str);
char	*ft_substr2(char *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		only_space(char *str);
int		ft_strlen2(char **str);
void    check_map_surrending(char **map);
void	free_str(char **str);
int		is_num(char *str);
int		ft_atoi(const char *str);
void 	print_data(t_data *data);
void    check_inside_map(char **map);


#endif