/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:06:20 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/25 21:36:55 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		pars_2(t_data *data, char *line)
{
	data->file.szx = 4;

	printf("%s\n", line);
	if (*line == 'R')
		return (1);
	else if (*line == 'N')
		return (1);
	else if (*line == 'S')
		return (1);
	else if (*line == 'W')
		return (1);
	else if (*line == 'E')
		return (1);
	else if (*line == 'S')
		return (1);
	else if (*line == 'F')
		return (1);
	else if (*line == 'C')
		return (1);
	else if (*line == '1')
		return (2);
	else
		return (-1);
}

int		pars_1(t_data *data)
{
	int i;
	char *line;

	while (data->file.file->next != NULL)
	{
		i = 0;
		line = data->file.file->content;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if(pars_2(data, &line[i]) == 2)
			exit(1);
		data->file.file = data->file.file->next;
	}
	return (1);
}

int     parser(t_data *data)
{
	char    *line;
	t_list	*first;

	line = NULL;
	write(1, "stpars\n", 7);
	get_next_line(data->file.fd, &line);
	data->file.file = ft_lstnew(line);
	first = data->file.file;
	while (get_next_line(data->file.fd, &line) == 1)
	{
		while (data->file.file->next)
			data->file.file = data->file.file->next;
		data->file.file->next = ft_lstnew(line);
	}
	data->file.file = first;
	write(1, "endpars\n", 8);
	pars_1(data);
	if (line != NULL)
		free(line);
	return (1);
}