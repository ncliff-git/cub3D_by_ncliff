/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:07:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/19 21:45:10 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "../includes/cub3D.h"

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

int s_rot(int keycode, t_data *img)
{
	if (keycode == 123)
		img->player.prot -= (0.1 * (SPEED_ROT / 10));
	if (keycode == 124)
		img->player.prot += (0.1 * (SPEED_ROT / 10));
	if (img->player.prot < 0)
		img->player.prot += 3.14 * 2;
	if (img->player.prot > 3.14 * 2)
		img->player.prot -= 3.14 * 2;
	printf("rot: %f\n", img->player.prot);
	return (1);
}

int	s_render(int keycode, t_data *img)
{
	int pdx;
	int pdy;

	pdx = cos(img->player.prot) * 3;
	pdy = sin(img->player.prot) * 3;
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(0);
	}
	printf("posX: %d", img->player.posX);
	printf("posY: %d", img->player.posY);
	if (keycode == 13)
	{
		img->player.posY += pdy;
		img->player.posX += pdx;
		if (worldMap[(img->player.posY - 5) / 20][img->player.posX / 20] == 1)
			img->player.posY += 2;
	}
	if (keycode == 0)
	{
		img->player.posY += pdy;
		img->player.posX -= pdx;
		if (worldMap[img->player.posY / 20][(img->player.posX - 5) / 20] == 1)
			img->player.posX += 2;
	}
	if (keycode == 1)
	{
		img->player.posY -= pdy;
		img->player.posX -= pdx;
		if (worldMap[(img->player.posY + 5) / 20][img->player.posX / 20] == 1)
			img->player.posY -= 2;
	}
	if (keycode == 2)
	{
		img->player.posY -= pdy;
		img->player.posX += pdx;
		if (worldMap[img->player.posY / 20][(img->player.posX + 5) / 20] == 1)
			img->player.posX -= 2;
	}
	s_rot(keycode, img);
	return (1);
}

int	loop_hook(t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img.img, 0, 0);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_pl.img, img->player.posX, img->player.posY);
	return (1);
}

int	main(void)
{
	t_data	img;
	
	img.player.posX = 240;
	img.player.posY = 240;
	img.player.prot = 1.57;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, screenWidth + 1, screenHeight + 1, "cub3D");
	img.img.img = mlx_new_image(img.mlx, screenWidth + 1, screenHeight + 1);
	img.img.addr = mlx_get_data_addr(img.img.img, &img.img.bits_per_pixel, &img.img.line_length, &img.img.endian);

	img.img_pl.img = mlx_new_image(img.mlx, 3, 3);
	img.img_pl.addr = mlx_get_data_addr(img.img_pl.img, &img.img_pl.bits_per_pixel, &img.img_pl.line_length, &img.img_pl.endian);

	plr_render(&img.img_pl, 3, 3);
	map_render(&img);

	mlx_hook(img.mlx_win, 2, 1L<<0, s_render, &img);
	mlx_key_hook(img.mlx_win, s_render, &img);

	mlx_loop_hook(img.mlx, &loop_hook, &img);
	mlx_loop(img.mlx);
}