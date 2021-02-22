/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:24:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/22 20:33:03 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void render3D(t_data *data)
{
	int	x;
	int i;
	double *z_buffer;
	
	x = 0;
	z_buffer = (double *)malloc(sizeof(double) * RES_X);
	while (x < RES_X)
	{
		ray_math_1(data, x);
		ray_math_2(data);
		wall_side(data);
		render_wall(data, x);
		z_buffer[x] = PW_DIST;
		x++;
	}
	sort_sp(data);
	i = 0;
	while (i < data->spr_sum)
    {
		sp_math(data, i);
		render_sp(data, &z_buffer);
		i++;
    }
	return ;
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
	R_DIRX = 0;
	R_DIRY = 0;
	P_MAPX = 0;
	P_MAPY = 0;
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
	
	F_CL[0] = -1;
	F_CL[1] = -1;
	F_CL[2] = -1;
	
	C_CL[0] = -1;
	C_CL[1] = -1;
	C_CL[2] = -1;

	return (1);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int pixel_take(t_img *img, int x, int y)
{
	unsigned int color;
	char	*dst;

	color = 0;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	loop_hook(t_data *data)
{
	render(data);
	key_move(data);
	mlx_clear_window(D_MLX, data->mlx_win);
	mlx_put_image_to_window(D_MLX, data->mlx_win, data->img_mp.img, 0, 0);
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
