/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:22:46 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:16 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	move_rot(t_data *data, int rot)
{
	double old_dirx;
	double planx_old;
	double speed;

	old_dirx = data->player.dirx;
	planx_old = data->player.planx;
	speed = SPEED_ROT;
	if (rot == 1)
		speed *= -1;
	data->player.dirx = data->player.dirx * cos(speed)
	- data->player.diry * sin(speed);
	data->player.diry = old_dirx * sin(speed)
	+ data->player.diry * cos(speed);
	data->player.planx = data->player.planx * cos(speed)
	- data->player.plany * sin(speed);
	data->player.plany = planx_old * sin(speed)
	+ data->player.plany * cos(speed);
	return (1);
}

int	move_up(t_data *data)
{
	if (data->file.map[(int)(data->player.posx + data->player.dirx
	* SPEED_MOVE)][(int)(data->player.posy)] != '1')
		data->player.posx += data->player.dirx * SPEED_MOVE;
	if (data->file.map[(int)(data->player.posx)][(int)(data->player.posy
	+ data->player.diry * SPEED_MOVE)] != '1')
		data->player.posy += data->player.diry * SPEED_MOVE;
	return (1);
}

int	move_dw(t_data *data)
{
	if (data->file.map[(int)(data->player.posx
	- data->player.dirx * SPEED_MOVE)]
	[(int)(data->player.posy - data->player.diry * SPEED_MOVE)] == '1')
		return (1);
	data->player.posx -= data->player.dirx * SPEED_MOVE;
	data->player.posy -= data->player.diry * SPEED_MOVE;
	return (1);
}

int	move_rt(t_data *data)
{
	if (data->file.map[(int)(data->player.posx
	+ (data->player.dirx * cos(-PI / 2)
	- data->player.diry * sin(-PI / 2)) * SPEED_MOVE)][(int)(data->player.posy
	+ (data->player.dirx * sin(-PI / 2) + data->player.diry
	* cos(-PI / 2)) * SPEED_MOVE)] == '1')
		return (1);
	data->player.posx += (data->player.dirx * cos(-PI / 2) - data->player.diry
	* sin(-PI / 2)) * SPEED_MOVE;
	data->player.posy += (data->player.dirx * sin(-PI / 2) + data->player.diry
	* cos(-PI / 2)) * SPEED_MOVE;
	return (1);
}

int	move_lt(t_data *data)
{
	if (data->file.map[(int)(data->player.posx
	+ (data->player.dirx * cos(PI / 2)
	- data->player.diry * sin(PI / 2)) * SPEED_MOVE)][(int)(data->player.posy
	+ (data->player.dirx * sin(PI / 2) + data->player.diry
	* cos(PI / 2)) * SPEED_MOVE)] == '1')
		return (1);
	data->player.posx += (data->player.dirx * cos(PI / 2) - data->player.diry
	* sin(PI / 2)) * SPEED_MOVE;
	data->player.posy += (data->player.dirx * sin(PI / 2) + data->player.diry
	* cos(PI / 2)) * SPEED_MOVE;
	return (1);
}
