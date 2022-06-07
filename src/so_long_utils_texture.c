/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:29:08 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/13 15:29:22 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	init_textures(t_data *data)
{
	data->text.sucess = 0;
	data->text.texture = init_tab_totem(data, TEXTURE);
	data->text.collectible = init_tab_totem(data, COLLECTIBLE);
	data->text.player = init_tab_totem(data, PLAYER);
	data->text.wall = init_tab_totem(data, WALL);
	data->text.exit = init_tab_totem(data, EXIT);
	return (0);
}

int	ft_tab_int_lcpy(int *dst, int *src, int dst_size)
{
	int	i;

	i = 0;
	if (!src)
		return (-1);
	if (!dst_size)
		return (-1);
	while (i < dst_size)
	{
		dst[i] = src[i];
		i++;
	}
	return (0);
}

int	*init_tab_totem(t_data *data, char *file_name)
{
	t_image	tmp;
	int		*totem;
	int		*var;

	totem = malloc(sizeof(int) * 1024);
	tmp.img_ptr = mlx_xpm_file_to_image
		(data->mlx_ptr, file_name, &tmp.width, &tmp.height);
	if (tmp.width != 32 || tmp.height != 32)
	{
		printf("Error\n%s file is not a 32*32 format", file_name);
		quit_game(data);
	}
	if (tmp.img_ptr == NULL)
	{
		printf("Error\n%s file is not valid", file_name);
		quit_game(data);
	}
	var = (void *)mlx_get_data_addr
		(tmp.img_ptr, &tmp.bits_per_pixel, &tmp.line_length, &tmp.endian);
	ft_tab_int_lcpy(totem, var, 32 * 32);
	mlx_destroy_image(data->mlx_ptr, tmp.img_ptr);
	data->text.sucess++;
	return (totem);
}
