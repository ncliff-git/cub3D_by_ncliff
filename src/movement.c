/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:22:46 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/22 19:50:56 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int move_rot(t_data *data, int rot)
{
	double oldDirX = DIR_X;
	double planxOld = PLAN_X;
	
	if (rot == 1)
	{
		DIR_X = DIR_X * cos(-SPEED_ROT) - DIR_Y * sin(-SPEED_ROT);
		DIR_Y = oldDirX * sin(-SPEED_ROT) + DIR_Y * cos(-SPEED_ROT);

		PLAN_X = PLAN_X * cos(-SPEED_ROT) - PLAN_Y * sin(-SPEED_ROT);
		PLAN_Y = planxOld * sin(-SPEED_ROT) + PLAN_Y * cos(-SPEED_ROT);
	}
	if (rot == -1)
	{
		DIR_X = DIR_X * cos(SPEED_ROT) - DIR_Y * sin(SPEED_ROT);
		DIR_Y = oldDirX * sin(SPEED_ROT) + DIR_Y * cos(SPEED_ROT);

		PLAN_X = PLAN_X * cos(SPEED_ROT) - PLAN_Y * sin(SPEED_ROT);
		PLAN_Y = planxOld * sin(SPEED_ROT) + PLAN_Y * cos(SPEED_ROT);
	}
	return (1);
}

// Сделать колизию

int	move_up(t_data *data)
{
	if (data->file.map[(int)(POS_X + DIR_X * SPEED_MOVE)][(int)(POS_Y)] != '1')
		POS_X += DIR_X * SPEED_MOVE;
    if (data->file.map[(int)(POS_X)][(int)(POS_Y + DIR_Y * SPEED_MOVE)] != '1')
		POS_Y += DIR_Y * SPEED_MOVE;
	return (1);
}

int	move_dw(t_data *data)
{
	if (data->file.map[(int)(POS_X - DIR_X * SPEED_MOVE)][(int)(POS_Y - DIR_Y * SPEED_MOVE)] == '1')
		return (1);
	POS_X -= DIR_X * SPEED_MOVE;
	POS_Y -= DIR_Y * SPEED_MOVE;
	return (1);
}

int	move_rt(t_data *data)
{
	if (data->file.map[(int)(POS_X + (DIR_X * cos(-PI/2) - DIR_Y * sin(-PI/2)) * SPEED_MOVE)][(int)(POS_Y + (DIR_X * sin(-PI/2) + DIR_Y * cos(-PI/2)) * SPEED_MOVE)] == '1')
		return (1);
	POS_X += (DIR_X * cos(-PI/2) - DIR_Y * sin(-PI/2)) * SPEED_MOVE;
	POS_Y += (DIR_X * sin(-PI/2) + DIR_Y * cos(-PI/2)) * SPEED_MOVE;	
	return (1);
}

int	move_lt(t_data *data)
{
	if (data->file.map[(int)(POS_X + (DIR_X * cos(PI/2) - DIR_Y * sin(PI/2)) * SPEED_MOVE)][(int)(POS_Y + (DIR_X * sin(PI/2) + DIR_Y * cos(PI/2)) * SPEED_MOVE)] == '1')
		return (1);
	POS_X += (DIR_X * cos(PI/2) - DIR_Y * sin(PI/2)) * SPEED_MOVE;
	POS_Y += (DIR_X * sin(PI/2) + DIR_Y * cos(PI/2)) * SPEED_MOVE;
	return (1);
}
