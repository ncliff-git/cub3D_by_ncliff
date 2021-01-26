/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:50:39 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/26 18:02:14 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		valid_map(t_data *data)
{
	int x;
	int y;

	x =	0;
	y = 0;
	while (x < data->file.szx)
	{
		if ((data->file.map[0][x] != ' ' && data->file.map[0][x] != '1') ||
		(data->file.map[data->file.szy][x] != ' ' && data->file.map[data->file.szy][x] != '1'))
			ft_printf("error");
		x++;
	}
	return (1);
}