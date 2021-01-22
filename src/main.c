/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:07:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/22 19:42:59 by ncliff           ###   ########.fr       */
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

void cub(t_data *img, int x, int y, unsigned long color)
{
	int cx;
	int cy;

	cx = 0;
	cy = 0;
	while (cx++ < screenWidth / propWidth)
	{
		while (cy++ < screenHeight / propHeight)
		{
			my_mlx_pixel_put(&img->img_mmp, (x) + cx, (y) + cy, color);
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
	while (mpw < mapWidth)
	{
		while (mph < mapHeight)
		{
			if (worldMap[mph][mpw] == 1)
				cub(img, x, y, 0x558D99AE);
			if (worldMap[mph][mpw] == 0)
				cub(img, x, y, 0x552B2D42);
			y += screenHeight / propHeight;
			mph += 1;
		}
		y = 0;
		x += screenWidth / propWidth;
		mph = 0;
		mpw += 1;
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
			my_mlx_pixel_put(img, sx, sy, 0x00f72585);
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
	while (worldMap[(int)(img->player.posy + lrot + pdy) / (screenHeight / propHeight)][(int)(img->player.posx + lrot + pdx) / (screenWidth / propWidth)] != 1)
	{
		pdx += cos(img->player.prot + lrot);
		pdy += sin(img->player.prot + lrot);
		i++;
		my_mlx_pixel_put(&img->img_mmp, img->player.posx + lrot + pdx, img->player.posy + lrot + pdy, 0x00FDFFB6);
	}
	return (i);
}

int render(t_data *img)
{
	float	i;
	int		sc;

	i = ((PI / 3) / 2) * -1;
	sc = -1;
	mlx_destroy_image(img->mlx, img->img_mmp.img);
	img->img_mmp.img = mlx_new_image(img->mlx, 240 + 1, 240 + 1);
	mlx_destroy_image(img->mlx, img->img_mp.img);
	img->img_mp.img = mlx_new_image(img->mlx, screenWidth, screenHeight); // Сделать define
	plr_render(&img->img_pl, 5, 5);
	map_render(img);
	while(i < ((PI / 3) / 2))
	{
		line(img, i);
		sc++;
		render3d(img, sc, line(img, i));
		i += ((PI / 3) / screenWidth);
	}
	printf("%d", sc);
	return (1);
}

int	loop_hook(t_data *img)
{
	render(img);
	key_move(img);
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_mp.img, 0, 0);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_mmp.img, 0, 0);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_pl.img, img->player.posx, img->player.posy);
	return (1);
}

int	main(void)
{
	t_data	img;
	
	//-- Конструктор
	img.player.posx = 40;
	img.player.posy = 40;
	img.player.prot = 4.77;

	img.flags.btn_dw = 0;
	img.flags.btn_lt = 0;
	img.flags.btn_rt = 0;
	img.flags.btn_up = 0;
	img.flags.rot = 0;
	img.flags.spd = 0;
	//--

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, screenWidth + 1, screenHeight + 1, "cub3D");
	
	img.img_mmp.img = mlx_new_image(img.mlx, 240 + 1, 240 + 1); // Сделать define
	img.img_mmp.addr = mlx_get_data_addr(img.img_mmp.img, &img.img_mmp.bits_per_pixel, &img.img_mmp.line_length, &img.img_mmp.endian);

	img.img_mp.img = mlx_new_image(img.mlx, screenWidth, screenHeight);
	img.img_mp.addr = mlx_get_data_addr(img.img_mp.img, &img.img_mp.bits_per_pixel, &img.img_mp.line_length, &img.img_mp.endian);

	img.img_pl.img = mlx_new_image(img.mlx, 5, 5);
	img.img_pl.addr = mlx_get_data_addr(img.img_pl.img, &img.img_pl.bits_per_pixel, &img.img_pl.line_length, &img.img_pl.endian);

	render(&img);

	mlx_hook(img.mlx_win, 2, 1L<<0, key_press, &img);
	mlx_key_hook(img.mlx_win, key_realize, &img);

	mlx_loop_hook(img.mlx, &loop_hook, &img);
	mlx_loop(img.mlx);
}