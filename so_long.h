/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:01:10 by imaalem           #+#    #+#             */
/*   Updated: 2021/11/29 11:01:12 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# define TEXTURE "textures/texture.xpm"
# define COLLECTIBLE "textures/collectible.xpm"
# define PLAYER "textures/player.xpm"
# define WALL "textures/wall.xpm"
# define EXIT "textures/exit.xpm"

typedef struct s_map
{
	int			nb_line;
	int			size_line;
	int			tab[4];
	int			x;
	int			y;
}				t_map;

typedef struct s_image
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			width;
	int			height;
	int			ply_x;
	int			ply_y;
}				t_image;

typedef struct s_texture
{
	int			*texture;
	int			*collectible;
	int			*player;
	int			*wall;
	int			*exit;
	int			sucess;
}				t_text;

typedef struct s_position
{
	int			pst_x;
	int			pst_y;
}				t_position;

typedef struct s_data
{
	int			x;
	int			y;
	t_position	pst;
	t_image		img;
	t_text		text;
	int			nb_collectible;
	void		*mlx_ptr;
	void		*window;
	int			width;
	int			height;
}				t_data;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		check_error(const char *ber);
char	**parse_the_map(char *ber, t_data *data);
int		ft_putstr(char *s);
void	ft_putchar(char c);
void	free_tab_char(int map_size, char **tab);
void	quit_game(t_data *data);
char	**init_map(char	*ber, int nb_line);
int		count_lines(char *ber);
int		check_lateral_wall(char **map, int nb_line, int size_line, int y);
int		check_walls(char **map, t_map *my_map, int x, int y);
int		ft_tab_int_lcpy(int *dst, int *src, int dst_size);
void	my_mlx_pixel_put(t_data *data, int x, int y, int *color);
int		*init_tab_totem(t_data *data, char *file_name);
int		treat_pixels(t_data *d);
int		init_textures(t_data *data);
int		full_check_up(t_data *data, int ac, char **av);
int		print_map(t_data *d);
void	free_tab_char_new(int map_size, char **tab);

#endif