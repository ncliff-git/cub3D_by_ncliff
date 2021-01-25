/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:17:38 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/24 22:08:35 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int drowline(int x, int colorR, t_data *data)
{
	int y;
	
	y = -1;
	//printf("%d\n", colorR);
	while (y++ < data->file.resy - 1)
	{
		if (y < data->player.drawstart && y > data->player.drawend)
			my_mlx_pixel_put(&data->img_mp, x, y, colorR);
	}
	return (1);
}
