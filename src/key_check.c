/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:57:41 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_press(int keycode, t_data *img)
{
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(1);
	}
	if (keycode == 13)
		img->flags.btn_up = 1;
	if (keycode == 0)
		img->flags.btn_lt = 1;
	if (keycode == 1)
		img->flags.btn_dw = 1;
	if (keycode == 2)
		img->flags.btn_rt = 1;
	if (keycode == 123)
		img->flags.rot = -1;
	if (keycode == 124)
		img->flags.rot = 1;
	if (keycode == 257)
		img->flags.spd = SHIFT_MOVE;
	if (keycode == 256)
		img->flags.spd = CTRL_MOVE;
	return (1);
}

int		key_realize(int keycode, t_data *img)
{
	(void)keycode;
	if (keycode == 13)
		img->flags.btn_up = 0;
	if (keycode == 0)
		img->flags.btn_lt = 0;
	if (keycode == 1)
		img->flags.btn_dw = 0;
	if (keycode == 2)
		img->flags.btn_rt = 0;
	if (keycode == 123)
		img->flags.rot = 0;
	if (keycode == 124)
		img->flags.rot = 0;
	if (keycode == 257)
		img->flags.spd = 0;
	if (keycode == 256)
		img->flags.spd = 0;
	return (1);
}

int		key_move(t_data *img)
{
	if (img->flags.btn_up == 1)
		move_up(img);
	if (img->flags.btn_dw == 1)
		move_dw(img);
	if (img->flags.btn_lt == 1)
		move_lt(img);
	if (img->flags.btn_rt == 1)
		move_rt(img);
	if (img->flags.rot == 1 || img->flags.rot == -1)
		move_rot(img, img->flags.rot);
	return (1);
}
