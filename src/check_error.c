/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:37:30 by imaalem           #+#    #+#             */
/*   Updated: 2021/12/05 16:37:32 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_type(char *ber)
{
	int		i;
	int		j;
	char	*type;

	i = 0;
	j = 3;
	type = ".ber";
	i = ft_strlen(ber);
	if (i <= 4)
		return (-1);
	while (j >= 0)
	{
		if (type[j] == ber[i - 1])
		{
			j--;
			i--;
		}
		else
			return (-2);
	}
	if (ber[i - 1] == '/')
		return (-3);
	return (0);
}

int	check_file(char *ber)
{
	int	fd;

	if (open(ber, O_NOFOLLOW) == -1)
	{
		ft_putstr("Error\nthe argument is a symbolic link or doesn't exist\n");
		return (-1);
	}
	if (open(ber, O_DIRECTORY) == 1)
	{
		ft_putstr("Error\nthe argument is a directory\n");
		return (-1);
	}
	fd = open(ber, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Error\nan error occured during the opening of the file\n");
		return (-1);
	}
	close(fd);
	return (fd);
}

int	check_error(const char *ber)
{
	int	fd;

	if (check_type((char *)ber) == -1)
	{
		ft_putstr("Error\nthe .ber most not be a hidden file\n");
		return (-1);
	}
	if (check_type((char *)ber) == -2)
	{
		ft_putstr("Error\nthe file is not a .ber\n");
		return (-1);
	}
	if (check_type((char *)ber) == -3)
	{
		ft_putstr("Error\nthe .ber most not be a hidden file\n");
		return (-1);
	}
	fd = check_file((char *)ber);
	if (fd == -1)
		return (-1);
	else
		return (fd);
}
