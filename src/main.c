/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:07:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/22 14:32:15 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub3D.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void cub(t_data *img, int x, int y)
{
	int cx;
	int cy;

	cx = 0;
	cy = 0;
	while (cx++ < 20)
	{
		while (cy++ < 20)
		{
			my_mlx_pixel_put(&img->img, (x) + cx, (y) + cy, 0x00FFFFFF);
		}
		cy = 0;
	}
}

int	map_render(t_data *img)
{
	int x = 0;
	int y = 0;
	int mpw = 0;
	int mph = 0;
	while (x < screenWidth && mpw < mapWidth)
	{
		while (y < screenHeight && mph < mapHeight)
		{
			if (worldMap[mpw][mph] == 1)
				cub(img, x, y);
			y += 20;
			mpw += 1;
		}
		y = 0;
		x += 20;
		mpw = 0;
		mph += 1;
	}
	return (1);
}

int plr_render(t_img *img, int pX, int pY)
{
	int sx;
	int sy;

	sx = -1;
	sy = -1;
	while (++sx < pX)
	{
		while (++sy < pY)
			my_mlx_pixel_put(img, sx, sy, 0x00FF0000);
		sy = -1;
	}
	return (1);
}

int line(t_data *img, float lrot)
{
	float pdx;
	float pdy;
	int i;

	i = 0;
	pdx = 0;
	pdy = 0;
	pdx = cos(img->player.prot + lrot);
	pdy = sin(img->player.prot + lrot);
	while (worldMap[(int)(img->player.posy + lrot + pdy)/20][(int)(img->player.posx + lrot + pdx)/20] != 1)
	{
		pdx += cos(img->player.prot + lrot);
		pdy += sin(img->player.prot + lrot);
		my_mlx_pixel_put(&img->img, img->player.posx + lrot + pdx, img->player.posy + lrot + pdy, 0x00FF00FF);
	}
	printf("prot: %f\n", img->player.prot);
	return (1);
}

int render(t_data *img)
{
	float i;

	i = -0.506;
	mlx_destroy_image(img->mlx, img->img.img);
	img->img.img = mlx_new_image(img->mlx, screenWidth + 1, screenHeight + 1);
	plr_render(&img->img_pl, 3, 3);
	map_render(img);
	while(i < 0.506)
	{
		line(img, i);
		i += 0.001;
	}
	return (1);
}

int	loop_hook(t_data *img)
{
	render(img);
	key_move(img);
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img.img, 0, 0);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_pl.img, img->player.posx, img->player.posy);
	return (1);
}

int	main(void)
{
	t_data	img;
	
	img.player.posx = 240;
	img.player.posy = 240;
	img.player.prot = 4.77;

	img.flags.btn_dw = 0;
	img.flags.btn_lt = 0;
	img.flags.btn_rt = 0;
	img.flags.btn_up = 0;
	img.flags.rot = 0;
	img.flags.spd = 0;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, screenWidth + 1, screenHeight + 1, "cub3D");
	img.img.img = mlx_new_image(img.mlx, screenWidth + 1, screenHeight + 1);
	img.img.addr = mlx_get_data_addr(img.img.img, &img.img.bits_per_pixel, &img.img.line_length, &img.img.endian);
	img.img_pl.img = mlx_new_image(img.mlx, 3, 3);
	img.img_pl.addr = mlx_get_data_addr(img.img_pl.img, &img.img_pl.bits_per_pixel, &img.img_pl.line_length, &img.img_pl.endian);

	render(&img);

	mlx_hook(img.mlx_win, 2, 1L<<0, key_press, &img);
	mlx_key_hook(img.mlx_win, key_realize, &img);

	mlx_loop_hook(img.mlx, &loop_hook, &img);
	mlx_loop(img.mlx);
}