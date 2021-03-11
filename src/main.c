/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:24:43 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/05 15:30:31 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				render_3d(t_data *data)
{
	int		x;
	int		i;
	double	*z_buffer;

	x = 0;
	z_buffer = (double *)malloc(sizeof(double) * data->file.resx);
	while (x < data->file.resx)
	{
		ray_math(data, &data->player, x);
		dda_math(data, &data->player);
		wall_side(data, &data->player);
		render_wall(data, x);
		z_buffer[x] = data->player.pwdist;
		x++;
	}
	sort_sp(data);
	i = 0;
	while (i < data->spr_sum)
	{
		sp_math(data, &data->player, i);
		render_sp(data, &data->player, &z_buffer);
		i++;
	}
	free(z_buffer);
	return ;
}

int					render(t_data *data)
{
	rendersky(data);
	render_3d(data);
	if (data->save == 1)
	{
		screenshot(data);
		exit(1);
	}
	return (1);
}

int					loop_hook(t_data *data)
{
	render(data);
	key_move(data);
	if (data->save != 1)
	{
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->img_mp.img, 0, 0);
	}
	return (1);
}

int					main(int argc, char **argv)
{
	t_data	data;

	init_test(&data, argc, argv);
	data.mlx = mlx_init();
	if (data.save != 1)
		data.mlx_win = mlx_new_window(data.mlx, data.file.resx + 1,
	data.file.resy + 1, "cub3d");
	data.img_mp.img = mlx_new_image(data.mlx, data.file.resx, data.file.resy);
	data.img_mp.addr = mlx_get_data_addr(data.img_mp.img,
	&data.img_mp.bits_per_pixel, &data.img_mp.line_length, &data.img_mp.endian);
	mlx_texture(&data);
	if (data.save != 1)
	{
		mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
		mlx_hook(data.mlx_win, 17, 1L << 5, exit_funk, &data);
		mlx_key_hook(data.mlx_win, key_realize, &data);
	}
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
