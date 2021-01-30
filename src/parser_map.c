/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:58:01 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/30 16:56:20 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	*ft_memset_m(void *ptr, int volue, size_t num)
{
	unsigned char *ptr2;

	ptr2 = (unsigned char *)ptr;
	ptr2[num] = 0;
	while (num-- > 0)
	{
		ptr2[num] = volue;
	}
	return (ptr);
}

static int	pars_map2(t_data *data, int x, int y)
{
	int		i;
	int		p;
	char	*line;

	i = 0;
	p = 0;
	if (!(data->file.map = (char **)malloc(sizeof(char *) * y + 1)))
		return (-1);
	while (i <= y)
	{
		data->file.map[i] = (char *)malloc(sizeof(char) * x + 2);
		data->file.map[i] = ft_memset_m(data->file.map[i], ' ', x);
		line = data->file.file->content;
		while (line[p] != 0 && p < x)
		{
			data->file.map[i][p] = line[p];
			p++;
		}
		data->file.file = data->file.file->next;
		p = 0;
		i++;
	}
	return (1);
}

int			pars_map(t_data *data)
{
	int		x;
	int		y;
	t_list	*first;

	x = 0;
	y = 0;
	first = data->file.file;
	while (data->file.file->next)
	{
		if (ft_strlen((char*)data->file.file->content) > (size_t)x)
			x = ft_strlen((char*)data->file.file->content);
		data->file.file = data->file.file->next;
		y++;
	}
	data->file.szx = x;
	data->file.szy = y;
	data->file.file = first;
	pars_map2(data, x, y);
	return (1);
}
