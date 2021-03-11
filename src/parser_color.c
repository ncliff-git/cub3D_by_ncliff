/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:00:05 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/05 16:12:09 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	int	atoi_iter_mini(int *data, int i, int dp, char *line)
{
	data[dp] = 0;
	if (!(line[i] >= '0' && line[i] <= '9'))
		return (-1);
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != '\0')
	{
		data[dp] = data[dp] * 10 + (line[i] - '0');
		if (data[dp] > 255)
			error_msg_exit("Color num");
		i++;
	}
	return (i);
}

static	int	sp_comma_skip(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i] != ',')
		return (-1);
	i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

int			pars_color(int *data, char *line)
{
	int	i;

	i = 0;
	if (*line != ' ')
		error_msg_exit("Color");
	while (line[i] == ' ')
		i++;
	if ((i = atoi_iter_mini(data, i, 0, line)) == -1)
		error_msg_exit("Color");
	if ((i = sp_comma_skip(line, i)) == -1)
		error_msg_exit("Color");
	if ((i = atoi_iter_mini(data, i, 1, line)) == -1)
		error_msg_exit("Color");
	if ((i = sp_comma_skip(line, i)) == -1)
		error_msg_exit("Color");
	if ((i = atoi_iter_mini(data, i, 2, line)) == -1)
		error_msg_exit("Color");
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		error_msg_exit("Color");
	if ((data[0] > 255 || data[1] > 255 || data[2] > 255)
	|| (data[0] < 0 || data[1] < 0 || data[2] < 0))
		error_msg_exit("Color");
	return (1);
}
