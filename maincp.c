/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maincp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:24:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/22 18:25:57 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//--------TEST---------//
//--------TEST---------//
//--------TEST---------//

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
		pixel_put(&info->img_mp, x, y, color);
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
			if (WORLD_MAP[data->player.mapx][data->player.mapy] == '1') data->player.hit = 1;
			if (WORLD_MAP[data->player.mapx][data->player.mapy] == '2') data->player.hit = 1;
			if (WORLD_MAP[data->player.mapx][data->player.mapy] == '3') data->player.hit = 1;
		}
		if (data->player.side == 0)
			data->player.pwdist = (data->player.mapx - data->player.posx + (1 - data->player.stepx) / 2) / rayDirX;
		else
			data->player.pwdist = (data->player.mapy - data->player.posy + (1 - data->player.stepy) / 2) / rayDirY;
		data->player.lineh = (int)(data->file.resy / data->player.pwdist);
		int drawStart = -data->player.lineh / 2 + data->file.resy / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = data->player.lineh / 2 + data->file.resy / 2;
		if (drawEnd >= data->file.resy)
			drawEnd = data->file.resy - 1;

		//
		// Часть с текстурой
		//
			write(1, "1\n", 2);

		double wallX;
		if (data->player.side == 0)
			wallX = data->player.posy + data->player.pwdist * rayDirY;
		else
			wallX = data->player.posx + data->player.pwdist * rayDirX;
		wallX -= floor((wallX));

		int texX = (int)(wallX * (double)TEX_WH);
		if (data->player.side == 0 && rayDirX > 0)
			texX = TEX_WH - texX - 1;
		if (data->player.side == 1 && rayDirY < 0)
			texX = TEX_WH - texX - 1;

		double step = 1.0 * TEX_HEIGHT / data->player.lineh;

		double texPos = (drawStart - data->file.resy / 2 + data->player.lineh / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			//int texY = (int)texPos & (TEX_HEIGHT - 1);
			write(1, "1\n", 2);
			texPos += step;
			pixel_put(&data->img_mp, x, y, pixel_take(&data->no_tx, x, y));
			//
		}

		//
		// часть с текстурой
		//

		//if (WORLD_MAP[data->player.mapx][data->player.mapy] == '1')
		//	color = 0x00eb596e;
		//else if (WORLD_MAP[data->player.mapx][data->player.mapy] == '2')
		//	color = 0x00F0FF00;
		//else if (WORLD_MAP[data->player.mapx][data->player.mapy] == '3')
		//	color = 0x000000FF;
		//if (data->player.side == 1)
		//	color = color / 2;
		//verLine(data, x, drawStart, drawEnd, color);
		x++;
	}
	return ;
}

int mlx_texture(t_data *data)
{
	int width;
	int height;

	write(1, "1\n", 2);
	if (!(NO_IMG = mlx_xpm_file_to_image(D_MLX, NO_FL, &width, &height)))
		return (-1);
	NO_ADDR = mlx_get_data_addr(NO_IMG, &data->no_tx.bits_per_pixel, &data->no_tx.line_length, &data->no_tx.endian);	
	if (!(SO_IMG = mlx_xpm_file_to_image(D_MLX, SO_FL, &width, &height)))
		return (-1);
	SO_ADDR = mlx_get_data_addr(SO_IMG, &data->so_tx.bits_per_pixel, &data->so_tx.line_length, &data->so_tx.endian);		
	if (!(WE_IMG = mlx_xpm_file_to_image(D_MLX, data->file.we_ture, &width, &height)))
		return (-1);
	WE_ADDR = mlx_get_data_addr(WE_IMG, &data->we_tx.bits_per_pixel, &data->we_tx.line_length, &data->we_tx.endian);		
	if (!(EA_IMG = mlx_xpm_file_to_image(D_MLX, data->file.ea_ture, &width, &height)))
		return (-1);
	EA_ADDR = mlx_get_data_addr(EA_IMG, &data->ea_tx.bits_per_pixel, &data->ea_tx.line_length, &data->ea_tx.endian);		
	return (1);
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
				pixel_put(&data->img_mp, x, y, create_trgb(0, data->file.f[0], data->file.f[1], data->file.f[2]));
			else if (data->file.resy > y)
				pixel_put(&data->img_mp, x, y, create_trgb(0, data->file.c[0], data->file.c[1], data->file.c[2]));
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
	//mlx_destroy_image(D_MLX, data->img_mp.img);
	//data->img_mp.img = mlx_new_image(D_MLX, data->file.resx, data->file.resy); // Сделать define
	rendersky(data);
	render3D(data);
	return (1);
}

//--------FINAL--------//
//--------FINAL--------//
//--------FINAL--------//

int data_constr(t_data *data)
{
	data->file.resx = 0;
	data->file.resy = 0;
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

int pixel_take(t_img *img, int x, int y)
{
	int color;
	char	*dst;

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
	write(1, "1\n", 2);
	render(data);
	key_move(data);
	mlx_clear_window(D_MLX, D_MLX_win);
	mlx_put_image_to_window(D_MLX, D_MLX_win, data->img_mp.img, 0, 0);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	argv[argc] = NULL;
	write(1, "1\n", 2);	
	data.file.fd = open(argv[1], O_RDONLY);
	data_constr(&data);
	if (parser(&data) == -1 || mlx_texture(&data) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}

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
		pixel_put(&info->img_mp, x, y, color);
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
			if (WORLD_MAP[data->player.mapx][data->player.mapy] == '1') data->player.hit = 1;
			if (WORLD_MAP[data->player.mapx][data->player.mapy] == '2') data->player.hit = 1;
			if (WORLD_MAP[data->player.mapx][data->player.mapy] == '3') data->player.hit = 1;
		}
		if (data->player.side == 0)
			data->player.pwdist = (data->player.mapx - data->player.posx + (1 - data->player.stepx) / 2) / rayDirX;
		else
			data->player.pwdist = (data->player.mapy - data->player.posy + (1 - data->player.stepy) / 2) / rayDirY;
		data->player.lineh = (int)(data->file.resy / data->player.pwdist);
		int drawStart = -data->player.lineh / 2 + data->file.resy / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = data->player.lineh / 2 + data->file.resy / 2;
		if (drawEnd >= data->file.resy)
			drawEnd = data->file.resy - 1;
		int	color;
		if (WORLD_MAP[data->player.mapx][data->player.mapy] == '1')
			color = 0x00eb596e;
		else if (WORLD_MAP[data->player.mapx][data->player.mapy] == '2')
			color = 0x00F0FF00;
		else if (WORLD_MAP[data->player.mapx][data->player.mapy] == '3')
			color = 0x000000FF;
		
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
				pixel_put(&data->img_mp, x, y, create_trgb(0, data->file.f[0], data->file.f[1], data->file.f[2]));
			else if (data->file.resy > y)
				pixel_put(&data->img_mp, x, y, create_trgb(0, data->file.c[0], data->file.c[1], data->file.c[2]));
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
	//mlx_destroy_image(D_MLX, data->img_mp.img);
	//data->img_mp.img = mlx_new_image(D_MLX, data->file.resx, data->file.resy); // Сделать define
	rendersky(data);
	render3D(data);
	return (1);
}

//--------FINAL--------//
//--------FINAL--------//
//--------FINAL--------//

int data_constr(t_data *data)
{
	data->file.resx = 0;
	data->file.resy = 0;
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
	mlx_clear_window(D_MLX, D_MLX_win);
	mlx_put_image_to_window(D_MLX, D_MLX_win, data->img_mp.img, 0, 0);
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