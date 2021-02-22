/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:58:50 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/22 20:33:09 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	sort_sp(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->spr_sum)
	{
		SPR_ORD[i] = i;
		SPR_DST[i] = ((POS_X - get_spr(data->spr, i, 'x')) *
		(POS_X - get_spr(data->spr, i, 'x'))
		+ (POS_Y - get_spr(data->spr, i, 'y'))
		* (POS_Y - get_spr(data->spr, i, 'y')));
		i++;
	}
	sortSprites(SPR_ORD, SPR_DST, data->spr_sum);
	return ;
}

void	sp_math(t_data *data, int i)
{
	SP_X = get_spr(data->spr, SPR_ORD[i], 'x') - POS_X;
	SP_Y = get_spr(data->spr, SPR_ORD[i], 'y') - POS_Y;
	INV_DET = 1.0 / (PLAN_X * DIR_Y - DIR_X * PLAN_Y);
	TRAN_X = INV_DET * (DIR_Y * SP_X - DIR_X * SP_Y);
	TRAN_Y = INV_DET * (-PLAN_Y * SP_X + PLAN_X * SP_Y);
	SPR_X = (int)((RES_X / 2) * (1 + TRAN_X / TRAN_Y));
	SPR_HT = abs((int)(RES_Y / (TRAN_Y)));
	DR_SP_ND_Y_ST_Y = -SPR_HT / 2 + RES_Y / 2;
	(DR_SP_ND_Y_ST_Y < 0) ? (DR_SP_ND_Y_ST_Y = 0) : 0;
	DR_SP_ND_Y = SPR_HT / 2 + RES_Y / 2;
	(DR_SP_ND_Y >= RES_Y) ? (DR_SP_ND_Y = RES_Y - 1) : 0;
	SPR_WT = abs((int)(RES_Y / (TRAN_Y)));
	DR_SP_ND_Y_ST_X = -SPR_WT / 2 + SPR_X;
	(DR_SP_ND_Y_ST_X < 0) ? (DR_SP_ND_Y_ST_X = 0) : 0;
	DR_SP_ND_Y_ND_X = SPR_WT / 2 + SPR_X;
	(DR_SP_ND_Y_ND_X >= RES_X) ? (DR_SP_ND_Y_ND_X = RES_X - 1) : 0;
	return ;
}

void	render_sp(t_data *data, double **z_b)
{
	int	stpe;
	int	y;
	int d;

	stpe = DR_SP_ND_Y_ST_X;
	while (stpe < DR_SP_ND_Y_ND_X)
	{
		y = DR_SP_ND_Y_ST_Y;
		SP_TX = (int)(256 * (stpe - (-SPR_WT / 2 + SPR_X))
		* TEX_WH / SPR_WT) / 256;
		if (TRAN_Y > 0 && stpe > 0 && stpe < RES_X && TRAN_Y < (*z_b)[stpe])
		{
			while (y < DR_SP_ND_Y)
			{
				d = (y) * 256 - RES_Y * 128 + SPR_HT * 128;
				SP_TY = ((d * TEX_HEIGHT) / SPR_HT) / 256;
				SP_CR = pixel_take(&data->s_tx, SP_TX, SP_TY);
				if ((SP_CR & 0x00FFFFFF) != 0)
					pixel_put(&data->img_mp, stpe, y, SP_CR);
				y++;
			}
		}
		stpe++;
	}
	return ;
}
