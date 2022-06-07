/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:34:09 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/07 18:34:11 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	close_window(t_data *data)
{
	quit_game(data);
	return (0);
}

int	move(t_data *data, int ply_x, int ply_y)
{
	if (data->img.map[ply_y][ply_x] == '1')
		return (0);
	if (data->img.map[ply_y][ply_x] == '0' ||
		data->img.map[ply_y][ply_x] == 'C' ||
		data->img.map[ply_y][ply_x] == 'P')
	{
		if (data->img.map[ply_y][ply_x] == 'C')
		{
			data->nb_collectible--;
			data->img.map[ply_y][ply_x] = '0';
		}
		my_mlx_pixel_put(data, data->pst.pst_x * 32,
			data->pst.pst_y * 32, data->text.texture);
		my_mlx_pixel_put(data, ply_x * 32, ply_y * 32, data->text.player);
		data->pst.pst_x = ply_x;
		data->pst.pst_y = ply_y;
		return (1);
	}
	if (data->img.map[ply_y][ply_x] == 'E' &&
		data->nb_collectible == 0)
	{
		ft_putstr("Darshad : hummm those pumpkins were delicious!\n");
		quit_game(data);
	}
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	int	beware;

	beware = 0;
	if (keycode == 65307)
		quit_game(data);
	else if (keycode == 97)
		beware = move(data, data->pst.pst_x - 1, data->pst.pst_y);
	else if (keycode == 115)
		beware = move(data, data->pst.pst_x, data->pst.pst_y + 1);
	else if (keycode == 100)
		beware = move(data, data->pst.pst_x + 1, data->pst.pst_y);
	else if (keycode == 119)
		beware = move(data, data->pst.pst_x, data->pst.pst_y - 1);
	if (beware != 0)
		mlx_put_image_to_window(data->mlx_ptr,
			data->window, data->img.img_ptr, 0, 0);
	return (0);
}

int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->window = mlx_new_window
		(data->mlx_ptr, data->width, data->height, "so_long");
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr
		(data->img.img_ptr, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	full_check_up(&data, ac, av);
	init_mlx(&data);
	if (init_textures(&data) == -1)
	{
		ft_putstr("Error\nall textures must be 32*32 formated\n");
		quit_game(&data);
	}
	print_map(&data);
	mlx_hook(data.window, 2, 1L << 0, key_press, &data);
	mlx_hook(data.window, 17, 1L << 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	quit_game(&data);
}
