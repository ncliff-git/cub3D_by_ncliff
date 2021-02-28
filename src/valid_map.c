/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:50:39 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/28 21:15:06 by ncliff           ###   ########.fr       */
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

static int	pos_map_choise(t_data *data)
{
	data->player.dirx = 0;
	data->player.diry = 0;
	data->player.planx = 0;
	data->player.plany = 0;
	if (data->file.stpos == 'N')
	{
		data->player.dirx = -1;
		data->player.plany = 0.66;
	}
	if (data->file.stpos == 'S')
	{
		data->player.dirx = 1;
		data->player.plany = -0.66;
	}
	if (data->file.stpos == 'W')
	{
		data->player.diry = -1;
		data->player.planx = -0.66;
	}
	if (data->file.stpos == 'E')
	{
		data->player.diry = 1;
		data->player.planx = 0.66;
	}
	return (0);
}

static int	pos_map(t_data *data)
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
				data->player.posx = y + 0.5;
				data->player.posy = x + 0.5;
				pos_map_choise(data);
			}
			x++;
		}
		y++;
	}
	return ((data->file.stpos == 0) ? 0 : 1);
}

int			other_char(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < data->file.szy)
	{
		while (x < data->file.szx)
		{
			if (data->file.map[y][x] != '0' && data->file.map[y][x] != '1'
			&& data->file.map[y][x] != '2' && data->file.map[y][x] != 'S'
			&& data->file.map[y][x] != 'N' && data->file.map[y][x] != 'W'
			&& data->file.map[y][x] != 'E' && data->file.map[y][x] != ' ')
				return (-1);
			x++;
		}
		x = 0;
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
			return (-1);
		x++;
	}
	if (!(close_map(data, '0', ' ') && close_map(data, 'N', ' ')
	&& close_map(data, 'S', ' ') && close_map(data, 'E', ' ')
	&& close_map(data, 'W', ' ') && close_map(data, '2', ' ')))
		return (-1);
	if (!(close_map(data, '0', '\0') && close_map(data, 'N', '\0')
	&& close_map(data, 'S', '\0') && close_map(data, 'E', '\0')
	&& close_map(data, 'W', '\0') && close_map(data, '2', '\0')))
		return (-1);
	if (pos_map(data) == 0)
		return (-1);
	if (other_char(data) == -1)
		return (-1);
	return (1);
}
