/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:50:39 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/27 19:53:47 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	close_map(t_data *data, char i, char s)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < data->file.szy)
	{
		while (x < data->file.szx)
		{
			if (data->file.map[y][x] == i && (data->file.map[y][x - 1] == s
			|| data->file.map[y][x + 1] == s
			|| data->file.map[y - 1][x] == s
			|| data->file.map[y + 1][x] == s
			|| data->file.map[y - 1][x - 1] == s
			|| data->file.map[y + 1][x + 1] == s
			|| data->file.map[y + 1][x - 1] == s
			|| data->file.map[y - 1][x + 1] == s))
				return (0);
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

int			pos_map(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->file.szy)
	{
		x = 0;
		while (x < data->file.szx)
		{
			if (data->file.map[y][x] == 'W' || data->file.map[y][x] == 'S'
			|| data->file.map[y][x] == 'E' || data->file.map[y][x] == 'N')
			{
				if (data->file.stpos != 0)
					return (0);
				data->file.stpos = data->file.map[y][x];
				data->player.posx = y;
				data->player.posy = x;
				// Добавть направление при спавне
			}
			x++;
		}
		y++;
	}
	return (1);
}

int			valid_map(t_data *data)
{
	int x;

	x = 0;
	data->file.stpos = 0;
	while (x < data->file.szx)
	{
		if ((data->file.map[0][x] != ' ' && data->file.map[0][x] != '1')
		|| (data->file.map[data->file.szy][x] != ' '
		&& data->file.map[data->file.szy][x] != '1'))
			exit(1);
		x++;
	}
	if (!(close_map(data, '0', ' ') && close_map(data, 'N', ' ')
	&& close_map(data, 'S', ' ') && close_map(data, 'E', ' ')
	&& close_map(data, 'W', ' ')))
		exit(1);
	if (!(close_map(data, '0', '\0') && close_map(data, 'N', '\0')
	&& close_map(data, 'S', '\0') && close_map(data, 'E', '\0')
	&& close_map(data, 'W', '\0')))
		exit(1);
	if(pos_map(data) == 0)
		exit(1);
	return (1);
}
