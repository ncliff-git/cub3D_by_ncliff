/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:24:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/21 21:18:02 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	verLine(t_data *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		my_mlx_pixel_put(&info->img_mp, x, y, color);
		y++;
	}
}





























void render_math_1(t_data *data, int x)
{
	P_CAM = 2 * x / (double)RES_X - 1;
	R_DIR_X = DIR_X + PLAN_X * P_CAM;
	R_DIR_Y = DIR_Y + PLAN_Y * P_CAM;
	P_MAP_X = (int)POS_X;
	P_MAP_Y = (int)POS_Y;
	D_DIST_X = fabs(1 / R_DIR_X);
	D_DIST_Y = fabs(1 / R_DIR_Y);
	HIT = 0;
	(R_DIR_X < 0) ? (STEP_X = -1) : 0;
	(R_DIR_X < 0) ? (S_DIST_X = (POS_X - P_MAP_X) * D_DIST_X) : 0;
	(R_DIR_X < 0) ? 0 : (STEP_X = 1);
	(R_DIR_X < 0) ? 0 : (S_DIST_X = (P_MAP_X + 1.0 - POS_X) * D_DIST_X);
	(R_DIR_Y < 0) ? (STEP_Y = -1) : 0;
	(R_DIR_Y < 0) ? (S_DIST_Y = (POS_Y - P_MAP_Y) * D_DIST_Y) : 0;
	(R_DIR_Y < 0) ? 0 : (STEP_Y = 1);
	(R_DIR_Y < 0) ? 0 : (S_DIST_Y = (P_MAP_Y + 1.0 - POS_Y) * D_DIST_Y);
	return ;
}

void render_math_2(t_data *data)
{
	while (HIT == 0)
	{
		if (S_DIST_X < S_DIST_Y)
		{
			S_DIST_X += D_DIST_X;
			P_MAP_X += STEP_X;
			SIDE = 0;
		}
		else
		{
			S_DIST_Y += D_DIST_Y;
			P_MAP_Y += STEP_Y;
			SIDE = 1;
		}
		if (WORLD_MAP[P_MAP_X][P_MAP_Y] == '1')
			HIT = 1;
	}
	(SIDE == 0) ? (PW_DIST = (P_MAP_X - POS_X + (1 - STEP_X) / 2) / R_DIR_X) : 0;
	(SIDE == 0) ? 0 : (PW_DIST = (P_MAP_Y - POS_Y + (1 - STEP_Y) / 2) / R_DIR_Y);
	LINE_H = (int)(RES_Y / PW_DIST);
	DR_START = -LINE_H / 2 + RES_Y / 2;
	(DR_START < 0) ? (DR_START = 0) : 0;
	DR_END = LINE_H / 2 + RES_Y / 2;
	(DR_END >= RES_Y) ? (DR_END = RES_Y - 1) : 0;
	return ;
}

void render_math_3(t_data *data)
{
	(SIDE == 0) ? (WALL_X = POS_Y + PW_DIST * R_DIR_Y) : 0;
	(SIDE == 0) ? 0 : (WALL_X = POS_X + PW_DIST * R_DIR_X);
	WALL_X -= floor((WALL_X));
	TEX_X = (int)(WALL_X * (double)TEX_WIDTH);
	(SIDE == 0 && R_DIR_X > 0) ? (TEX_X = TEX_WIDTH - TEX_X - 1) : 0;
	(SIDE == 1 && R_DIR_Y < 0) ? (TEX_X = TEX_WIDTH - TEX_X - 1) : 0;
	STEP = 1.0 * TEX_HEIGHT / LINE_H;
	TEX_POS = (DR_START - RES_Y / 2 + LINE_H / 2) * STEP;
	return ;
}

void render_math_4(t_data *data, int x)
{
	int y;
	
	y = DR_START;
	while (y < DR_END)
	{
		if (SIDE == 0)
		{
			if(STEP_X > 0)
			{
				TEX_Y = (int)TEX_POS & (TEX_HEIGHT - 1);
				TEX_POS += STEP;
				my_mlx_pixel_put(&data->img_mp, x, y, my_mlx_pixel_take(&data->so_tx, TEX_X, TEX_Y));
			}
			else
			{
				TEX_Y = (int)TEX_POS & (TEX_HEIGHT - 1);
				TEX_POS += STEP;
				my_mlx_pixel_put(&data->img_mp, x, y, my_mlx_pixel_take(&data->no_tx, TEX_X, TEX_Y));
			}
		}
		else
		{
			if (STEP_Y > 0)
			{
				TEX_Y = (int)TEX_POS & (TEX_HEIGHT - 1);
				TEX_POS += STEP;
				my_mlx_pixel_put(&data->img_mp, x, y, my_mlx_pixel_take(&data->ea_tx, TEX_X, TEX_Y));
			}
			else
			{
				TEX_Y = (int)TEX_POS & (TEX_HEIGHT - 1);
				TEX_POS += STEP;
				my_mlx_pixel_put(&data->img_mp, x, y, my_mlx_pixel_take(&data->we_tx, TEX_X, TEX_Y));
			}
		}
		y++;
	}
	return ;
}

void render_sp_math_1(t_data *data)
{
	int i;

	i = 0;
	while (i < data->spr_sum)
    {
		SPR_ORD[i] = i;
		SPR_DST[i] = ((POS_X - get_spr(data->spr, i, 'x')) * (POS_X - get_spr(data->spr, i, 'x')) + (POS_Y - get_spr(data->spr, i, 'y')) * (POS_Y - get_spr(data->spr, i, 'y')));
		i++;
	}
	sortSprites(SPR_ORD, SPR_DST, data->spr_sum);
	return ;
}

void render_sp_math_2(t_data *data, int i)
{
	SP_X = get_spr(data->spr, SPR_ORD[i], 'x') - POS_X;
	SP_Y = get_spr(data->spr, SPR_ORD[i], 'y') - POS_Y;
	INV_DET = 1.0 / (PLAN_X * DIR_Y - DIR_X * PLAN_Y);
	TRAN_X = INV_DET * (DIR_Y * SP_X - DIR_X * SP_Y);
	TRAN_Y = INV_DET * (-PLAN_Y * SP_X + PLAN_X * SP_Y);
	SPR_SCR_X = (int) ((RES_X / 2) * (1 + TRAN_X / TRAN_Y));
	SPR_HT = abs((int) (RES_Y / (TRAN_Y)));
	DR_SP_ST_Y = -SPR_HT / 2 + RES_Y / 2;
	(DR_SP_ST_Y < 0) ? (DR_SP_ST_Y = 0) : 0;
	DR_SP_ND_Y = SPR_HT / 2 + RES_Y / 2;
	(DR_SP_ND_Y >= RES_Y) ? (DR_SP_ND_Y = RES_Y - 1) : 0;
	SPR_WT = abs( (int) (RES_Y / (TRAN_Y)));
	DR_SP_ST_X = -SPR_WT / 2 + SPR_SCR_X;
	(DR_SP_ST_X < 0) ? (DR_SP_ST_X = 0) : 0;
	DR_SP_ND_X = SPR_WT / 2 + SPR_SCR_X;
	(DR_SP_ND_X >= RES_X) ? (DR_SP_ND_X = RES_X - 1) : 0;
	return ;
}

void render_sp_math_3(t_data *data, double **zBuffer)
{
	int stripe;
	int y;
	
	stripe = DR_SP_ST_X;
	while (stripe < DR_SP_ND_X)
	{
		y = DR_SP_ST_Y;
		SP_TEX_X = (int) (256 * (stripe - (-SPR_WT / 2 + SPR_SCR_X)) * TEX_WIDTH / SPR_WT) / 256;
		if(TRAN_Y > 0 && stripe > 0 && stripe < RES_X && TRAN_Y < (*zBuffer)[stripe])
		while (y < DR_SP_ND_Y)
		{
			int d = (y) * 256 - RES_Y * 128 + SPR_HT * 128;
			SP_TEX_Y = ((d * TEX_HEIGHT) / SPR_HT) / 256;
			SP_CR = my_mlx_pixel_take(&data->s_tx, SP_TEX_X, SP_TEX_Y);
			if ((SP_CR & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&data->img_mp, stripe, y, SP_CR);
			y++;
		}
		stripe++;
	}
	return ;
}




void render3D(t_data *data)
{
	int	x;
	int i;
	double *zBuffer;
	
	x = 0;
	zBuffer = (double *)malloc(sizeof(double) * RES_X);
	while (x < RES_X)
	{
		render_math_1(data, x);
		render_math_2(data);
		render_math_3(data);
		render_math_4(data, x);
		zBuffer[x] = PW_DIST;
		x++;
	}
	render_sp_math_1(data);
	i = 0;
	while (i < data->spr_sum)
    {
		render_sp_math_2(data, i);
		render_sp_math_3(data, &zBuffer);
		i++;
    }
	return ;
}






























int mlx_texture(t_data *data)
{
	int width;
	int height;

	data->no_tx.img = mlx_new_image(data->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!(data->no_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.no_ture, &width, &height)))
		return (-1);
	data->no_tx.addr = mlx_get_data_addr(data->no_tx.img, &data->no_tx.bits_per_pixel, &data->no_tx.line_length, &data->no_tx.endian);
	data->so_tx.img = mlx_new_image(data->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!(data->so_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.so_ture, &width, &height)))
		return (-1);
	data->so_tx.addr = mlx_get_data_addr(data->so_tx.img, &data->so_tx.bits_per_pixel, &data->so_tx.line_length, &data->so_tx.endian);
	data->we_tx.img = mlx_new_image(data->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!(data->we_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.we_ture, &width, &height)))
		return (-1);
	data->we_tx.addr = mlx_get_data_addr(data->we_tx.img, &data->we_tx.bits_per_pixel, &data->we_tx.line_length, &data->we_tx.endian);	
	data->ea_tx.img = mlx_new_image(data->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!(data->ea_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.ea_ture, &width, &height)))
		return (-1);
	data->ea_tx.addr = mlx_get_data_addr(data->ea_tx.img, &data->ea_tx.bits_per_pixel, &data->ea_tx.line_length, &data->ea_tx.endian);
	data->s_tx.img = mlx_new_image(data->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!(data->s_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.s_ture, &width, &height)))
		return (-1);
	data->s_tx.addr = mlx_get_data_addr(data->s_tx.img, &data->s_tx.bits_per_pixel, &data->s_tx.line_length, &data->s_tx.endian);
	return (1);
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
				my_mlx_pixel_put(&data->img_mp, x, y, create_trgb(0, data->file.f[0], data->file.f[1], data->file.f[2]));
			else if (RES_Y > y)
				my_mlx_pixel_put(&data->img_mp, x, y, create_trgb(0, data->file.c[0], data->file.c[1], data->file.c[2]));
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int render(t_data *data)
{
	rendersky(data);
	render3D(data);
	return (1);
}

int data_constr(t_data *data)
{
	RES_X = -1;
	data->file.resy = -1;
	P_CAM = 0;
	R_DIR_X = 0;
	R_DIR_Y = 0;
	P_MAP_X = 0;
	P_MAP_Y = 0;
	S_DIST_X = 0;
	S_DIST_Y = 0;
	D_DIST_X = 0;
	D_DIST_Y = 0;
	STEP_X = 0;
	STEP_Y = 0;
	HIT = 0;
	SIDE = 0;
	LINE_H = 0;
	DR_END = 0;
	DR_START = 0;
	data->player.prot = 0;
	data->flags.btn_dw = 0;
	data->flags.btn_lt = 0;
	data->flags.btn_rt = 0;
	data->flags.btn_up = 0;
	data->flags.rot = 0;
	data->flags.spd = 0;
	HIT = 0;
	
	data->file.f[0] = -1;
	data->file.f[1] = -1;
	data->file.f[2] = -1;
	
	data->file.c[0] = -1;
	data->file.c[1] = -1;
	data->file.c[2] = -1;

	return (1);
}

unsigned int my_mlx_pixel_take(t_img *img, int x, int y)
{
	unsigned int color;
	char	*dst;

	color = 0;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	loop_hook(t_data *data)
{
	render(data);
	key_move(data);
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_mp.img, 0, 0);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	argv[argc] = NULL;	
	data.file.fd = open(argv[1], O_RDONLY);
	data_constr(&data);
	if (parser(&data) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	if (data.file.f[0] == -1 || data.file.f[1] == -1 || data.file.f[2] == -1
	|| data.file.c[0] == -1 || data.file.c[1] == -1 || data.file.c[2] == -1
	|| data.file.resx == -1 || data.file.resy == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	data.spr_sum = malloc_spr(&data);
	
	data.spriteDistance = (double *)malloc(sizeof(double) * data.spr_sum);
	data.spriteOrder = (int *)malloc(sizeof(int) * data.spr_sum);

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.file.resx + 1, data.file.resy + 1, "cub3D");
	data.img_mp.img = mlx_new_image(data.mlx, data.file.resx, data.file.resy);
	data.img_mp.addr = mlx_get_data_addr(data.img_mp.img, &data.img_mp.bits_per_pixel, &data.img_mp.line_length, &data.img_mp.endian);

	if (mlx_texture(&data) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}

	mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
	mlx_key_hook(data.mlx_win, key_realize, &data);

	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
