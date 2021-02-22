/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:51:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/22 21:07:36 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_wall_1(t_data *data, int x, int y)
{
	if (STEP_X > 0)
	{
		TEX_Y = (int)TEX_POS;
		TEX_POS += STEP;
		pixel_put(&data->img_mp, x, y, pixel_take(&data->so_tx, TEX_X, TEX_Y));
	}
	else
	{
		TEX_Y = (int)TEX_POS;
		TEX_POS += STEP;
		pixel_put(&data->img_mp, x, y, pixel_take(&data->no_tx, TEX_X, TEX_Y));
	}
}

void	render_wall_2(t_data *data, int x, int y)
{
	if (STEP_Y > 0)
	{
		TEX_Y = (int)TEX_POS;
		TEX_POS += STEP;
		pixel_put(&data->img_mp, x, y, pixel_take(&data->ea_tx, TEX_X, TEX_Y));
	}
	else
	{
		TEX_Y = (int)TEX_POS;
		TEX_POS += STEP;
		pixel_put(&data->img_mp, x, y, pixel_take(&data->we_tx, TEX_X, TEX_Y));
	}
}

void	render_wall(t_data *data, int x)
{
	int	y;

	y = DR_START - 1;
	while (++y < DR_END)
		if (SIDE == 0)
			render_wall_1(data, x, y);
		else
			render_wall_2(data, x, y);
	return ;
}
