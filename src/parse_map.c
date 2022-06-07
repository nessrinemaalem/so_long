/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:00:41 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/05 18:00:42 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	read_the_map(char **map, t_map *m)
{
	while (m->y < m->nb_line)
	{
		while (m->x < m->size_line - 2)
		{
			if (map[m->y][m->x] == 'C')
				m->tab[0] = m->tab[0] + 1;
			else if (map[m->y][m->x] == 'P')
				m->tab[1] = m->tab[1] + 1;
			else if (map[m->y][m->x] == 'E')
				m->tab[2] = 1;
			else if (map[m->y][m->x] == '0' || map[m->y][m->x] == '1' )
				m->tab[3] = 1;
			else
			{
				ft_putstr("Error\nthe map can only contain 0 , 1, P, C and E\n");
				return (-1);
			}
			m->x++;
		}
		m->x = 1;
		m->y++;
	}
	return (0);
}

int	check_elements(char **map, t_map *my_map, t_data *data)
{
	my_map->tab[0] = 0;
	my_map->tab[1] = 0;
	my_map->tab[2] = 0;
	my_map->tab[3] = 0;
	read_the_map(map, my_map);
	if (my_map->tab[1] > 1)
	{
		ft_putstr("Error\nthe game can only have one player\n");
		return (-1);
	}
	if (my_map->tab[0] == 0 || my_map->tab[1] == 0 || my_map->tab[2] == 0)
		return (-1);
	data->nb_collectible = my_map->tab[0];
	return (0);
}

int	map_is_rectangle(char **map, int nb_line)
{
	size_t	size_line;
	int		i;

	i = 0;
	size_line = ft_strlen(map[i]);
	while (i < nb_line - 1)
	{
		if (ft_strlen(map[i]) == size_line)
			i++;
		else
			return (-1);
		if (!ft_strchr(map[i], '\n'))
		{
			if (ft_strlen(map[i]) != (size_line - 1))
				return (-1);
		}
		else
		{
			if (ft_strlen(map[i]) != size_line)
				return (-1);
		}
	}
	return (0);
}

int	check_map(char **map, t_map *my_map, t_data *data)
{
	my_map->size_line = ft_strlen(map[0]);
	my_map->x = 0;
	my_map->y = 0;
	if (map_is_rectangle(map, my_map->nb_line) == -1)
	{
		ft_putstr("Error\nthe map is not rectangular\n");
		return (-1);
	}
	if (check_walls(map, my_map, 0, 0) == -1)
	{
		ft_putstr("Error\nthe map must be surrounded by walls\n");
		return (-1);
	}
	if (check_elements(map, my_map, data) == -1)
	{
		ft_putstr("Error\nthe map must at least contain (P), (C) and (E)\n");
		return (-1);
	}
	data->width = (my_map->size_line - 1) * 32;
	return (0);
}

char	**parse_the_map(char *ber, t_data *data)
{
	char	**map;
	t_map	my_map;

	my_map.nb_line = count_lines(ber);
	data->height = my_map.nb_line * 32;
	if (my_map.nb_line <= 2)
	{
		ft_putstr("Error\nthe map is too small\n");
		return (NULL);
	}
	map = init_map(ber, my_map.nb_line);
	if (check_map(map, &my_map, data) == -1)
	{
		printf("mince\n");
		free_tab_char(my_map.nb_line, map);
		exit (1);
	}
	return (map);
}
