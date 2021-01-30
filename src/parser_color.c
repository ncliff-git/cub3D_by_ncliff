/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:00:05 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/30 16:51:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static	int	atoi_iter_mini(int *data, int i, int dp, char *line)
{
	data[dp] = 0;
	if (!(line[i] >= '0' && line[i] <= '9'))
		return (-1);
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != '\0')
	{
		data[dp] = data[dp] * 10 + (line[i] - '0');
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
		return (-1);
	while (line[i] == ' ')
		i++;
	if ((i = atoi_iter_mini(data, i, 0, line)) == -1)
		return (-1);
	if ((i = sp_comma_skip(line, i)) == -1)
		return (-1);
	if ((i = atoi_iter_mini(data, i, 1, line)) == -1)
		return (-1);
	if ((i = sp_comma_skip(line, i)) == -1)
		return (-1);
	if ((i = atoi_iter_mini(data, i, 2, line)) == -1)
		return (-1);
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (-1);
	if ((data[0] > 255 || data[1] > 255 || data[2] > 255)
	|| (data[0] < 0 || data[1] < 0 || data[2] < 0))
		return (-1);
	return (1);
}
