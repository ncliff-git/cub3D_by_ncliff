/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:03:35 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/26 17:56:02 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	pars_r2(int *data, char *line)
{
	int i;

	i = 0;
	if (line[i] != ' ')
		return (-1);
	else
	{
		while (line[i] == ' ')
			i++;
		while ((line[i] >= '0' && line[i] <= '9') && line[i] != '\0')
		{
			*data = *data * 10 + (line[i] - '0');
			i++;
		}
		if (line[i] != ' ' && line[i] != '\0')
			return (-1);
	}
	return (i);
}

int			pars_res(t_data *data, char *line)
{
	data->file.resx = 0;
	data->file.resy = 0;
	if (pars_r2(&data->file.resy, &line[pars_r2(&data->file.resx, line)]) == -1)
		return (-1);
	(data->file.resx < 640) ? data->file.resx = 640 : 0;
	(data->file.resx > 2560) ? data->file.resx = 2560 : 0;
	(data->file.resy < 480) ? data->file.resy = 480 : 0;
	(data->file.resy > 1440) ? data->file.resy = 1440 : 0;
	return (1);
}
