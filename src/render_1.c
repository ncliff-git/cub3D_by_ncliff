/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:56:47 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/22 21:02:34 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int mlx_texture(t_data *data)
{
	NO_IMG = mlx_new_image(D_MLX, TEX_WH, TEX_HEIGHT);
	if (!(NO_IMG = mlx_xpm_file_to_image(D_MLX, NO_FL, &NO_X, &NO_Y)))
		return (-1);
	NO_ADDR = mlx_get_data_addr(NO_IMG, &NO_PX_BIT, &NO_LINE_L, &NO_ENDIAN);
	SO_IMG = mlx_new_image(D_MLX, TEX_WH, TEX_HEIGHT);
	if (!(SO_IMG = mlx_xpm_file_to_image(D_MLX, SO_FL, &SO_X, &SO_Y)))
		return (-1);
	SO_ADDR = mlx_get_data_addr(SO_IMG, &SO_PX_BIT, &SO_LINE_L, &SO_ENDIAN);
	WE_IMG = mlx_new_image(D_MLX, TEX_WH, TEX_HEIGHT);
	if (!(WE_IMG = mlx_xpm_file_to_image(D_MLX, WE_FL, &WE_X, &WE_Y)))
		return (-1);
	WE_ADDR = mlx_get_data_addr(WE_IMG, &WE_PX_BIT, &WE_LINE_L, &WE_ENDIAN);	
	EA_IMG = mlx_new_image(D_MLX, TEX_WH, TEX_HEIGHT);
	if (!(EA_IMG = mlx_xpm_file_to_image(D_MLX, EA_FL, &EA_X, &EA_Y)))
		return (-1);
	EA_ADDR = mlx_get_data_addr(EA_IMG, &EA_PX_BIT, &EA_LINE_L, &EA_ENDIAN);
	S_IMG = mlx_new_image(D_MLX, TEX_WH, TEX_HEIGHT);
	if (!(S_IMG = mlx_xpm_file_to_image(D_MLX, S_FL, &S_X, &S_Y)))
		return (-1);
	S_ADDR = mlx_get_data_addr(S_IMG, &S_PX_BIT, &S_LINE_L, &S_ENDIAN);
	return (1);
}

void	ray_math_1(t_data *data, int x)
{
	P_CAM = 2 * x / (double)RES_X - 1;
	R_DIRX = DIR_X + PLAN_X * P_CAM;
	R_DIRY = DIR_Y + PLAN_Y * P_CAM;
	P_MAPX = (int)POS_X;
	P_MAPY = (int)POS_Y;
	D_DIST_X = fabs(1 / R_DIRX);
	D_DIST_Y = fabs(1 / R_DIRY);
	HIT = 0;
	(R_DIRX < 0) ? (STEP_X = -1) : 0;
	(R_DIRX < 0) ? (S_DIST_X = (POS_X - P_MAPX) * D_DIST_X) : 0;
	(R_DIRX < 0) ? 0 : (STEP_X = 1);
	(R_DIRX < 0) ? 0 : (S_DIST_X = (P_MAPX + 1.0 - POS_X) * D_DIST_X);
	(R_DIRY < 0) ? (STEP_Y = -1) : 0;
	(R_DIRY < 0) ? (S_DIST_Y = (POS_Y - P_MAPY) * D_DIST_Y) : 0;
	(R_DIRY < 0) ? 0 : (STEP_Y = 1);
	(R_DIRY < 0) ? 0 : (S_DIST_Y = (P_MAPY + 1.0 - POS_Y) * D_DIST_Y);
	return ;
}

void	ray_math_2(t_data *data)
{
	while (HIT == 0)
	{
		if (S_DIST_X < S_DIST_Y)
		{
			S_DIST_X += D_DIST_X;
			P_MAPX += STEP_X;
			SIDE = 0;
		}
		else
		{
			S_DIST_Y += D_DIST_Y;
			P_MAPY += STEP_Y;
			SIDE = 1;
		}
		if (WORLD_MAP[P_MAPX][P_MAPY] == '1')
			HIT = 1;
	}
	(SIDE == 0) ? (PW_DIST = (P_MAPX - POS_X + (1 - STEP_X) / 2) / R_DIRX) : 0;
	(SIDE == 0) ? 0 : (PW_DIST = (P_MAPY - POS_Y + (1 - STEP_Y) / 2) / R_DIRY);
	LINE_H = (int)(RES_Y / PW_DIST);
	DR_START = -LINE_H / 2 + RES_Y / 2;
	(DR_START < 0) ? (DR_START = 0) : 0;
	DR_END = LINE_H / 2 + RES_Y / 2;
	(DR_END >= RES_Y) ? (DR_END = RES_Y - 1) : 0;
	return ;
}

void	wall_side(t_data *data)
{
	(SIDE == 0) ? (WALL_X = POS_Y + PW_DIST * R_DIRY) : 0;
	(SIDE == 0) ? 0 : (WALL_X = POS_X + PW_DIST * R_DIRX);
	WALL_X -= floor((WALL_X));
	int w;
	if (SIDE == 0)
	{
		if (STEP_X > 0)
		{
			w = SO_X;
			data->player.h = SO_Y;
		}
		else
		{
			w = NO_X;
			data->player.h = NO_Y;
		}
	}
	else
	{
		if (STEP_Y > 0)
		{
			w = EA_X;
			data->player.h = EA_Y;
		}
		else
		{
			w = WE_X;
			data->player.h = WE_Y;
		}
	}
	TEX_X = (int)(WALL_X * (double)(w));
	(SIDE == 0 && R_DIRX > 0) ? (TEX_X = (w) - TEX_X - 1) : 0;
	(SIDE == 1 && R_DIRY < 0) ? (TEX_X = (w) - TEX_X - 1) : 0;
	STEP = 1.0 * data->player.h / LINE_H;
	TEX_POS = (DR_START - RES_Y / 2 + LINE_H / 2) * STEP;
	return ;
}

int rendersky(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (x < RES_X)
	{
		while (y < RES_Y)
		{
			if (RES_Y/2 > y)
				pixel_put(&data->img_mp, x, y, create_trgb(0, F_CL[0], F_CL[1], F_CL[2]));
			else if (RES_Y > y)
				pixel_put(&data->img_mp, x, y, create_trgb(0, C_CL[0], C_CL[1], C_CL[2]));
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}