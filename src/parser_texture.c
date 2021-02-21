/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:30:33 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/21 14:53:12 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		pars_texture(char **texture, char s, char *line)
{
	int	i;
	int	len;
	int	fd;

	i = 2;
	fd = 0;
	if (s == ' ')
		i = 1;
	else if (*line != s || *(line + 1) != ' ')
		return (-1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	len = ft_strlen(&line[i]);
	if (len < 5)
		return (-1);
	if (line[i + len - 4] != '.' && line[i + len - 3] != 'x'
	&& line[i + len - 2] != 'p'
	&& line[i + len - 1] != 'm')
		return (-1);
	if (open(&line[i], fd, O_RDONLY) == -1)
	{
		close(fd);
		return (-1);
	}
	return ((!(*texture = ft_strdup(&line[i]))) ? -1 : 1);
}
