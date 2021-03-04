/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:51:27 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/04 19:03:59 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	malloc_spr2(t_data *data, int x, int y)
{
	static int	i;

	data->spr[i].posx = x + 0.5;
	data->spr[i].posy = y + 0.5;
	data->spr[i].dist = 0.0;
	i++;
	return (1);
}

int			malloc_spr(t_data *data)
{
	int x;
	int y;
	int sum;

	x = 0;
	sum = 0;
	while (data->file.szx > x)
	{
		y = 0;
		while (data->file.szy > y)
		{
			if (data->file.map[y][x] == '2')
				sum++;
			y++;
		}
		x++;
	}
	data->spr_sum = sum;
	data->spr = malloc(sum * sizeof(t_spr));
	x = 0;
	while (data->file.szx > x)
	{
		y = 0;
		while (data->file.szy > y)
		{
			if (data->file.map[y][x] == '2')
				malloc_spr2(data, x, y);
			y++;
		}
		x++;
	}
	return (sum);
}
