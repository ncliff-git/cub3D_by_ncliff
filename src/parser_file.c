/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:06:20 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/27 16:52:59 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int		pars_2(t_data *data, char *line)
{
	data->file.szx = 4;
	if (*line == 'R')
		return (pars_res(data, &line[1]));
	else if (*line == 'N')
		return (pars_texture(&NO_FL, 'O', &line[1]));
	else if (*line == 'S' && *(line + 1) == 'O')
		return (pars_texture(&SO_FL, 'O', &line[1]));
	else if (*line == 'W')
		return (pars_texture(&data->file.we_ture, 'E', &line[1]));
	else if (*line == 'E')
		return (pars_texture(&data->file.ea_ture, 'A', &line[1]));
	else if (*line == 'S')
		return (pars_texture(&data->file.s_ture, ' ', &line[1]));
	else if (*line == 'F')
		return (pars_color(data->file.f, &line[1]));
	else if (*line == 'C')
		return (pars_color(data->file.c, &line[1]));
	else if (*line == '1')
		return ((pars_map(data) == 1) ? 2 : -2);
	else if (*line == '\0')
		return (1);
	else
	{
		write (1, (line), 1);
		write (1, "\n", 1);
		return (-1);
	}
	return (1);
}

static int		pars_1(t_data *data)
{
	int		i;
	int		res;
	char	*line;
	t_list	*first;

	first = data->file.file;
	res = 0;
	while (data->file.file->next != NULL)
	{
		i = 0;
		line = data->file.file->content;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		res = pars_2(data, &line[i]);
		if (res == -2)
			error_msg_exit("Map");
		if (res == -1)
		{
			data->file.file = first;
			return (-1);
		}
		else if (res == 2)
			return (2);
		data->file.file = data->file.file->next;
	}
	data->file.file = first;
	return (1);
}

int				parser(t_data *data)
{
	char	*line;
	t_list	*first;

	line = NULL;
	get_next_line(data->file.fd, &line);
	data->file.file = ft_lstnew(line);
	first = data->file.file;
	while (get_next_line(data->file.fd, &line) == 1)
	{
		while (data->file.file->next)
			data->file.file = data->file.file->next;
		data->file.file->next = ft_lstnew(line);
	}
	while (data->file.file->next)
		data->file.file = data->file.file->next;
	data->file.file->next = ft_lstnew(line);
	data->file.file = first;
	if (pars_1(data) == -1)
		error_msg_exit("None info");
	if (data->map_check != 1)
		error_msg_exit("Map");
	// тут ошибка
	ft_lstclear(&data->file.file, free);
	if (line != NULL)
		free(line);	
	return ((valid_map(data) == -1) ? -1 : 1);
}
