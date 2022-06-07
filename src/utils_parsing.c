/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:13:45 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/13 16:13:49 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	finish_read(int fd)
{
	char	*tmp;

	tmp = NULL;
	if (tmp == get_next_line(fd))
	{
		if (tmp)
			free(tmp);
	}
}

char	**init_map(char	*ber, int nb_line)
{
	int		fd;
	int		i;
	char	**map;

	i = 0;
	fd = open(ber, O_RDONLY);
	map = (malloc(sizeof(char *) * nb_line));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	while (i < nb_line)
		map[i++] = get_next_line(fd);
	finish_read(fd);
	return (map);
}

int	count_lines(char *ber)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(ber, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close (fd);
	return (i);
}

int	check_lateral_wall(char **map, int nb_line, int size_line, int y)
{
	while (y < nb_line - 1)
	{
		if (map[y][0] == '1' && map[y][size_line - 2] == '1')
			y++;
		else
			return (-1);
	}
	return (0);
}

int	check_walls(char **map, t_map *my_map, int x, int y)
{
	while (x < my_map->size_line)
	{
		if (map[y][x] != '1' && map[y][x] != '\n')
			return (-1);
		x++;
	}
	y = my_map->nb_line - 1;
	while (map[y][x])
	{
		if (map[y][x] == '1')
			x++;
		else
			return (-1);
	}
	y = 0;
	if (check_lateral_wall(map, my_map->nb_line, my_map->size_line, y) == -1)
		return (-1);
	return (0);
}
