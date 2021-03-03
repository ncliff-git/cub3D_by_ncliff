/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:03:35 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 21:17:24 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	pars_r2(int *data, char *line)
{
	int i;

	i = 0;
	if (line[i] != ' ' && line[i] != '\t')
		return (-1);
	else
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			return (-1);
		while ((line[i] >= '0' && line[i] <= '9') && line[i] != '\0')
		{
			*data = *data * 10 + (line[i] - '0');
			if (*data > 999999)
				*data = 999999;
			i++;
		}
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			return (-1);
	}
	return (i);
}

int			pars_res(t_data *data, char *line)
{
	int i;
	int h;
	int w;

	i = 0;
	mlx_get_screen_size(&w, &h);
	if (data->file.res_ch != 0)
		error_msg_exit("Double res");
	data->file.resx = 0;
	data->file.resy = 0;
	if ((i = pars_r2(&data->file.resx, line)) == -1)
		error_msg_exit("Res");
	if ((i += pars_r2(&data->file.resy, &line[i])) == -1)
		error_msg_exit("Res");
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			error_msg_exit("Res");
		i++;
	}
	(data->file.resx == 0 || data->file.resy == 0) ? error_msg_exit("Res") : 0;
	(data->file.resx > w) ? data->file.resx = w : 0;
	(data->file.resy > h) ? data->file.resy = h : 0;
	data->file.res_ch = 1;
	return (1);
}
