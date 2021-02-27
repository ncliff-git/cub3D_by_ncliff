/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:51:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/27 17:06:17 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_wall_1(t_data *data, t_player *pl, int x, int y)
{
	if (pl->stepx > 0)
	{
		pl->tex_y = (int)pl->tex_pos;
		pl->tex_pos += pl->step;
		pixel_put(&data->img_mp, x, y,
		pixel_take(&data->so_tx, pl->tex_x, pl->tex_y));
	}
	else
	{
		pl->tex_y = (int)pl->tex_pos;
		pl->tex_pos += pl->step;
		pixel_put(&data->img_mp, x, y,
		pixel_take(&data->no_tx, pl->tex_x, pl->tex_y));
	}
}

void	render_wall_2(t_data *data, t_player *pl, int x, int y)
{
	if (pl->stepy > 0)
	{
		pl->tex_y = (int)pl->tex_pos;
		pl->tex_pos += pl->step;
		pixel_put(&data->img_mp, x, y,
		pixel_take(&data->ea_tx, pl->tex_x, pl->tex_y));
	}
	else
	{
		pl->tex_y = (int)pl->tex_pos;
		pl->tex_pos += pl->step;
		pixel_put(&data->img_mp, x, y,
		pixel_take(&data->we_tx, pl->tex_x, pl->tex_y));
	}
}

void	render_wall(t_data *data, int x)
{
	int	y;

	y = data->player.drawstart - 1;
	while (++y < data->player.drawend)
		if (data->player.side == 0)
			render_wall_1(data, &data->player, x, y);
		else
			render_wall_2(data, &data->player, x, y);
	return ;
}
