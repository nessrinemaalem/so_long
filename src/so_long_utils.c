/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:04:54 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/13 13:04:56 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_tab_char(int map_size, char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (i < map_size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_char_new(int map_size, char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (i < map_size)
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

void	quit_game(t_data *data)
{
	ft_putstr("Goodbye buddy\n");
	free_tab_char(data->height / 32, data->img.map);
	if (data->text.sucess >= 1)
		free(data->text.texture);
	if (data->text.sucess >= 2)
		free(data->text.wall);
	if (data->text.sucess >= 3)
		free(data->text.player);
	if (data->text.sucess >= 4)
		free(data->text.collectible);
	if (data->text.sucess >= 5)
		free(data->text.exit);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->window);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (1);
}

int	treat_pixels(t_data *d)
{
	while (d->y < (d->height / 32))
	{
		while (d->x < (d->width / 32))
		{
			if (d->img.map[d->y][d->x] == '1')
				my_mlx_pixel_put(d, d->x * 32, d->y * 32, d->text.wall);
			else if (d->img.map[d->y][d->x] == '0')
				my_mlx_pixel_put(d, d->x * 32, d->y * 32, d->text.texture);
			else if (d->img.map[d->y][d->x] == 'C')
				my_mlx_pixel_put(d, d->x * 32, d->y * 32, d->text.collectible);
			else if (d->img.map[d->y][d->x] == 'P')
			{
				d->pst.pst_x = d->x;
				d->pst.pst_y = d->y;
				my_mlx_pixel_put(d, d->x * 32, d->y * 32, d->text.player);
			}
			else if (d->img.map[d->y][d->x] == 'E')
				my_mlx_pixel_put(d, d->x * 32, d->y * 32, d->text.exit);
			d->x++;
		}
		d->x = 0;
		d->y++;
	}
	return (0);
}

int	print_map(t_data *d)
{
	d->x = 0;
	d->y = 0;
	treat_pixels(d);
	mlx_put_image_to_window
		(d->mlx_ptr, d->window, d->img.img_ptr, 0, 0);
	return (0);
}
