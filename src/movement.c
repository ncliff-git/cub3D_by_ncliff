/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:22:46 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/25 14:15:10 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int move_rot(t_data *img, int rot)
{
	double oldDirX = img->player.dirx;
	double planxOld = img->player.planx;
	
	if (rot == 1)
	{
		img->player.dirx = img->player.dirx * cos(-SPEED_ROT) - img->player.diry * sin(-SPEED_ROT);
		img->player.diry = oldDirX * sin(-SPEED_ROT) + img->player.diry * cos(-SPEED_ROT);

		img->player.planx = img->player.planx * cos(-SPEED_ROT) - img->player.plany * sin(-SPEED_ROT);
		img->player.plany = planxOld * sin(-SPEED_ROT) + img->player.plany * cos(-SPEED_ROT);
	}
	if (rot == -1)
	{
		img->player.dirx = img->player.dirx * cos(SPEED_ROT) - img->player.diry * sin(SPEED_ROT);
		img->player.diry = oldDirX * sin(SPEED_ROT) + img->player.diry * cos(SPEED_ROT);

		img->player.planx = img->player.planx * cos(SPEED_ROT) - img->player.plany * sin(SPEED_ROT);
		img->player.plany = planxOld * sin(SPEED_ROT) + img->player.plany * cos(SPEED_ROT);
	}
	return (1);
}

// Сделать колизию

int	move_up(t_data *img)
{
	img->player.posx += img->player.dirx * SPEED_MOVE;
	img->player.posy += img->player.diry * SPEED_MOVE;
	return (1);
}

int	move_dw(t_data *img)
{
	img->player.posx -= img->player.dirx * SPEED_MOVE;
	img->player.posy -= img->player.diry * SPEED_MOVE;
	return (1);
}

int	move_rt(t_data *img)
{
	img->player.posx += (img->player.dirx * cos(-PI/2) - img->player.diry * sin(-PI/2)) * SPEED_MOVE;
	img->player.posy += (img->player.dirx * sin(-PI/2) + img->player.diry * cos(-PI/2)) * SPEED_MOVE;	
	return (1);
}

int	move_lt(t_data *img)
{
	img->player.posx += (img->player.dirx * cos(PI/2) - img->player.diry * sin(PI/2)) * SPEED_MOVE;
	img->player.posy += (img->player.dirx * sin(PI/2) + img->player.diry * cos(PI/2)) * SPEED_MOVE;
	return (1);
}
