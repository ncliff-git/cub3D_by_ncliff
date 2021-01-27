/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:24:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/27 19:52:28 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//--------TEST---------//
//--------TEST---------//
//--------TEST---------//

// int worldMap[24][24]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

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

void render3D(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->file.resx)
	{
		double cameraX = 2 * x / (double)data->file.resx - 1;
		double rayDirX = data->player.dirx + data->player.planx * cameraX;
		double rayDirY = data->player.diry + data->player.plany * cameraX;
		data->player.mapx = (int)data->player.posx;
		data->player.mapy = (int)data->player.posy;
		data->player.ddistx = fabs(1 / rayDirX);
		data->player.ddisty = fabs(1 / rayDirY);
		data->player.hit = 0;
		if (rayDirX < 0)
		{
			data->player.stepx = -1;
			data->player.sdistx = (data->player.posx - data->player.mapx) * data->player.ddistx;
		}
		else
		{
			data->player.stepx = 1;
			data->player.sdistx = (data->player.mapx + 1.0 - data->player.posx) * data->player.ddistx;
		}
		if (rayDirY < 0)
		{
			data->player.stepy = -1;
			data->player.sdisty = (data->player.posy - data->player.mapy) * data->player.ddisty;
		}
		else
		{
			data->player.stepy = 1;
			data->player.sdisty = (data->player.mapy + 1.0 - data->player.posy) * data->player.ddisty;
		}
		while (data->player.hit == 0)
		{
			if (data->player.sdistx < data->player.sdisty)
			{
				data->player.sdistx += data->player.ddistx;
				data->player.mapx += data->player.stepx;
				data->player.side = 0;
			}
			else
			{
				data->player.sdisty += data->player.ddisty;
				data->player.mapy += data->player.stepy;
				data->player.side = 1;
			}
			if (WORLD_MAP[data->player.mapx][data->player.mapy] > '0') data->player.hit = 1;
		}
		if (data->player.side == 0)
			data->player.pwdist = (data->player.mapx - data->player.posx + (1 - data->player.stepx) / 2) / rayDirX;
		else
			data->player.pwdist = (data->player.mapy - data->player.posy + (1 - data->player.stepy) / 2) / rayDirY;
		data->player.lineh = (int)(data->file.resy / data->player.pwdist);
		int drawStart = -data->player.lineh / 2 + data->file.resy / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = data->player.lineh / 2 + data->file.resy / 2;
		if(drawEnd >= data->file.resy)
			drawEnd = data->file.resy - 1;
		int	color;
		if (WORLD_MAP[data->player.mapx][data->player.mapy] == '1')
			color = 0x00eb596e;
		else if (WORLD_MAP[data->player.mapx][data->player.mapy] == '2')
			color = 0x00F0FF00;
		else if (WORLD_MAP[data->player.mapx][data->player.mapy] == '3')
			color = 0x000000FF;
		else
			color = 0x00FFFF00;
		
		if (data->player.side == 1)
			color = color / 2;
		verLine(data, x, drawStart, drawEnd, color);
		x++;
	}
	return ;
}

int rendersky(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (x < data->file.resx)
	{
		while (y < data->file.resy)
		{
			if (data->file.resy/2 > y)
				my_mlx_pixel_put(&data->img_mp, x, y, 0x00bbf1fa);
			else if (data->file.resy > y)
				my_mlx_pixel_put(&data->img_mp, x, y, 0x00c19277);
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int render(t_data *data)
{
	//Меньше лагов ели не дистроить//
	//mlx_destroy_image(data->mlx, data->img_mp.img);
	//data->img_mp.img = mlx_new_image(data->mlx, data->file.resx, data->file.resy); // Сделать define
	rendersky(data);
	render3D(data);
	return (1);
}

//--------FINAL--------//
//--------FINAL--------//
//--------FINAL--------//

int data_constr(t_data *data)
{
	//data->file.resx = 1280;
	//data->file.resy = 720;
//	data->player.posx = 10;
//	data->player.posy = 10;
	//
	data->player.dirx = -1;
	data->player.diry = 0;
	
	data->player.planx = 0;
	data->player.plany = 0.66;
	//
	data->player.cam = 0;
	data->player.raydirx = 0;
	data->player.raydiry = 0;
	data->player.mapx = 0;
	data->player.mapy = 0;
	data->player.sdistx = 0;
	data->player.sdisty = 0;
	data->player.ddistx = 0;
	data->player.ddisty = 0;
	data->player.stepx = 0;
	data->player.stepy = 0;
	data->player.hit = 0;
	data->player.side = 0;
	data->player.lineh = 0;
	data->player.drawend = 0;
	data->player.drawstart = 0;
	data->player.prot = 0;
	data->flags.btn_dw = 0;
	data->flags.btn_lt = 0;
	data->flags.btn_rt = 0;
	data->flags.btn_up = 0;
	data->flags.rot = 0;
	data->flags.spd = 0;
	data->player.hit = 0;
	return (1);
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
	parser(&data);
	ft_printf("\n%d\n%d\n", data.file.resx, data.file.resy);

	data_constr(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.file.resx + 1, data.file.resy + 1, "cub3D");
	data.img_mp.img = mlx_new_image(data.mlx, data.file.resx, data.file.resy);
	data.img_mp.addr = mlx_get_data_addr(data.img_mp.img, &data.img_mp.bits_per_pixel, &data.img_mp.line_length, &data.img_mp.endian);

	mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
	mlx_key_hook(data.mlx_win, key_realize, &data);

	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}