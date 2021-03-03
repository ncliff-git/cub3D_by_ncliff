/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_and_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:50:03 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				error_msg_exit(char *str)
{
	int i;

	i = ft_strlen(str);
	write(1, "\033[0;31mError\n", 13);
	if (i > 0)
	{
		write(1, str, i);
		write(1, "\n", 1);
	}
	exit(1);
}

int					exit_funk(t_data *img)
{
	mlx_destroy_window(img->mlx, img->mlx_win);
	exit(1);
}

int					create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int		pixel_take(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*dst;

	color = 0;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void				pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
