/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:56:47 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/28 14:27:15 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ray_math(t_data *data, t_player *pl, int x)
{
	pl->cam = 2 * x / (double)data->file.resx - 1;
	pl->rdirx = pl->dirx + pl->planx * pl->cam;
	pl->rdiry = pl->diry + pl->plany * pl->cam;
	pl->mapx = (int)pl->posx;
	pl->mapy = (int)pl->posy;
	pl->ddistx = fabs(1 / pl->rdirx);
	pl->ddisty = fabs(1 / pl->rdiry);
	pl->hit = 0;
	(pl->rdirx < 0) ? (pl->stepx = -1) : 0;
	(pl->rdirx < 0) ? (pl->sdistx = (pl->posx - pl->mapx) * pl->ddistx) : 0;
	(pl->rdirx < 0) ? 0 : (pl->stepx = 1);
	(pl->rdirx < 0) ? 0 : (pl->sdistx = (pl->mapx + 1.0
	- pl->posx) * pl->ddistx);
	(pl->rdiry < 0) ? (pl->stepy = -1) : 0;
	(pl->rdiry < 0) ? (pl->sdisty = (pl->posy
	- pl->mapy) * pl->ddisty) : 0;
	(pl->rdiry < 0) ? 0 : (pl->stepy = 1);
	(pl->rdiry < 0) ? 0 : (pl->sdisty = (pl->mapy + 1.0
	- pl->posy) * pl->ddisty);
	return ;
}

void	dda_math(t_data *data, t_player *pl)
{
	while (pl->hit == 0)
	{
		if (pl->sdistx < pl->sdisty)
		{
			pl->sdistx += pl->ddistx;
			pl->mapx += pl->stepx;
			pl->side = 0;
		}
		else
		{
			pl->sdisty += pl->ddisty;
			pl->mapy += pl->stepy;
			pl->side = 1;
		}
		if (data->file.map[pl->mapx][pl->mapy] == '1')
			pl->hit = 1;
	}
	return ;
}

void	textur_sizes(t_player *pl, t_img *tex)
{
	pl->w = tex->sp_x;
	pl->h = tex->sp_y;
}

void	wall_side_2(t_data *data)
{
	if (SIDE == 0)
	{
		if (STEP_X > 0)
			textur_sizes(&data->player, &data->so_tx);
		else
			textur_sizes(&data->player, &data->no_tx);
	}
	else
	{
		if (STEP_Y > 0)
			textur_sizes(&data->player, &data->ea_tx);
		else
			textur_sizes(&data->player, &data->we_tx);
	}
}

void	wall_side(t_data *data, t_player *pl)
{
	(pl->side == 0) ? (pl->pwdist = (pl->mapx - pl->posx
	+ (1 - pl->stepx) / 2) / pl->rdirx) : 0;
	(pl->side == 0) ? 0 : (pl->pwdist = (pl->mapy - pl->posy
	+ (1 - pl->stepy) / 2) / pl->rdiry);
	pl->lineh = (int)(data->file.resy / pl->pwdist);
	pl->drawstart = -pl->lineh / 2 + data->file.resy / 2;
	(pl->drawstart < 0) ? (pl->drawstart = 0) : 0;
	pl->drawend = pl->lineh / 2 + data->file.resy / 2;
	(pl->drawend >= data->file.resy) ? (pl->drawend = data->file.resy - 1) : 0;
	(pl->side == 0) ? (pl->wall_x = pl->posy + pl->pwdist * pl->rdiry) : 0;
	(pl->side == 0) ? 0 : (pl->wall_x = pl->posx + pl->pwdist * pl->rdirx);
	pl->wall_x -= floor((pl->wall_x));
	wall_side_2(data);
	pl->tex_x = (int)(pl->wall_x * (double)(pl->w));
	(pl->side == 0 && pl->rdirx > 0) ? (pl->tex_x = (pl->w)
	- pl->tex_x - 1) : 0;
	(pl->side == 1 && pl->rdiry < 0) ? (pl->tex_x = (pl->w)
	- pl->tex_x - 1) : 0;
	pl->step = 1.0 * pl->h / pl->lineh;
	pl->tex_pos = (pl->drawstart - data->file.resy / 2
	+ pl->lineh / 2) * pl->step;
	return ;
}
