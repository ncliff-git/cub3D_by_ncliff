/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:58:50 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sp(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->spr_sum)
	{
		data->spriteorder[i] = i;
		data->spritedistance[i] = ((data->player.posx
		- get_spr(data->spr, i, 'x'))
		* (data->player.posx - get_spr(data->spr, i, 'x'))
		+ (data->player.posy - get_spr(data->spr, i, 'y'))
		* (data->player.posy - get_spr(data->spr, i, 'y')));
		i++;
	}
	sort_sprites(data->spriteorder, data->spritedistance, data->spr_sum);
	return ;
}

void	sp_math(t_data *data, t_player *pl, int i)
{
	pl->sprite_x = get_spr(data->spr, data->spriteorder[i], 'x') - pl->posx;
	pl->sprite_y = get_spr(data->spr, data->spriteorder[i], 'y') - pl->posy;
	pl->inv_det = 1.0 / (pl->planx * pl->diry - pl->dirx * pl->plany);
	pl->tran_x = pl->inv_det * (pl->diry
	* pl->sprite_x - pl->dirx * pl->sprite_y);
	pl->tran_y = pl->inv_det * (-pl->plany
	* pl->sprite_x + pl->planx * pl->sprite_y);
	pl->spr_scr_x = (int)((data->file.resx / 2)
	* (1 + pl->tran_x / pl->tran_y));
	pl->spr_height = abs((int)(data->file.resy / (pl->tran_y)));
	pl->dr_st_sp_y = -pl->spr_height / 2 + data->file.resy / 2;
	(pl->dr_st_sp_y < 0) ? (pl->dr_st_sp_y = 0) : 0;
	pl->dr_nd_sp_y = pl->spr_height / 2 + data->file.resy / 2;
	(pl->dr_nd_sp_y >= data->file.resy) ?
	(pl->dr_nd_sp_y = data->file.resy - 1) : 0;
	pl->spr_widht = abs((int)(data->file.resy / (pl->tran_y)));
	pl->dr_st_sp_x = -pl->spr_widht / 2 + pl->spr_scr_x;
	(pl->dr_st_sp_x < 0) ? (pl->dr_st_sp_x = 0) : 0;
	pl->dr_nd_sp_x = pl->spr_widht / 2 + pl->spr_scr_x;
	(pl->dr_nd_sp_x >= data->file.resx) ?
	(pl->dr_nd_sp_x = data->file.resx - 1) : 0;
	return ;
}

void	sp_pixel_put(t_data *data, int *y, int *d, int stpe)
{
	*d = (*y) * 256 - data->file.resy * 128 + data->player.spr_height * 128;
	data->player.sp_tex_y = ((*d * data->s_tx.sp_y)
	/ data->player.spr_height) / 256;
	data->player.color_sp = pixel_take(&data->s_tx,
	data->player.sp_tex_x, data->player.sp_tex_y);
	if ((data->player.color_sp & 0x00FFFFFF) != 0)
		pixel_put(&data->img_mp, stpe, *y, data->player.color_sp);
	(*y)++;
}

void	render_sp(t_data *data, t_player *pl, double **z_b)
{
	int	stpe;
	int	y;
	int d;

	stpe = pl->dr_st_sp_x;
	while (stpe < pl->dr_nd_sp_x)
	{
		y = pl->dr_st_sp_y;
		pl->sp_tex_x = (int)(256 * (stpe - (-pl->spr_widht / 2 + pl->spr_scr_x))
		* data->s_tx.sp_x / pl->spr_widht) / 256;
		if (pl->tran_y > 0 && stpe > 0
		&& stpe < data->file.resx && pl->tran_y < (*z_b)[stpe])
		{
			while (y < pl->dr_nd_sp_y)
			{
				sp_pixel_put(data, &y, &d, stpe);
			}
		}
		stpe++;
	}
	return ;
}

int		rendersky(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (x < data->file.resx)
	{
		while (y < data->file.resy)
		{
			if (data->file.resy / 2 > y)
				pixel_put(&data->img_mp, x, y,
				create_trgb(0, data->file.f[0], data->file.f[1],
				data->file.f[2]));
			else if (data->file.resy > y)
				pixel_put(&data->img_mp, x, y,
				create_trgb(0, data->file.c[0], data->file.c[1],
				data->file.c[2]));
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}
