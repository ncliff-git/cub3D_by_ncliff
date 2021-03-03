/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_dop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:02:34 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	valid_param_2(t_data *data, char ch, char ch2)
{
	if (ch == 'E')
		data->file.ea_ch = 1;
	if (ch == 'S' && ch2 == ' ' && data->file.s_ch == 1)
		error_msg_exit("Double s tex");
	else if (ch == 'S' && ch2 == ' ')
		data->file.s_ch = 1;
	if (ch == 'F' && data->file.f_ch == 1)
		error_msg_exit("Double f tex");
	else if (ch == 'F')
		data->file.f_ch = 1;
	if (ch == 'C' && data->file.c_ch == 1)
		error_msg_exit("Double c tex");
	else if (ch == 'C')
		data->file.c_ch = 1;
}

int		pars1_dop(t_data *data, t_list *first, int res)
{
	if (res == -2)
		error_msg_exit("Map");
	if (res == -1)
	{
		data->file.file = first;
		return (-1);
	}
	else if (res == 2)
		return (2);
	return (1);
}
