/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_general.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:40:24 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/13 15:40:36 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	full_check_up(t_data *data, int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("Error\nso_long must be executed with one map\n");
		exit (1);
	}
	if (check_error(av[1]) == -1)
		exit (1);
	data->img.map = parse_the_map(av[1], data);
	if (data->img.map == NULL)
	{	
		ft_putstr("Error\nsomething wrong with malloc map");
		exit (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int *color)
{
	char	*dst;
	int		y_max;
	int		x_max;
	int		i;

	i = 0;
	y_max = y + 32;
	x_max = x + 32;
	while (y < y_max)
	{
		while (x < x_max)
		{
			dst = data->img.addr + (y * data->img.line_length
					+ x * (data->img.bits_per_pixel / 8));
			*(unsigned int *)dst = color[i];
			x++;
			i++;
		}
		x = x - 32;
		y++;
	}
}
