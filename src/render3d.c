/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:37:26 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/22 19:50:21 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		render3d(t_data *img, int width, int lenray)
{
	int y;

	y = -1;
	while (y++ < screenHeight - 1)
	{
		if (y < lenray)
		{
			my_mlx_pixel_put(&img->img_mp, width, y, 0x009D6B53);
			my_mlx_pixel_put(&img->img_mp, width, (screenHeight - 1) - y, 0x009D6B53);
		}
	}
	return (1);
}