/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:07:13 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/05 16:25:12 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				data_constr_2(t_data *data)
{
	data->file.resx = -1;
	data->file.resy = -1;
	data->player.cam = 0;
	data->player.rdirx = 0;
	data->player.rdiry = 0;
	data->player.mapx = 0;
	data->player.mapy = 0;
	data->player.sdistx = 0;
	data->player.sdisty = 0;
	data->player.ddistx = 0;
	data->player.ddisty = 0;
	data->player.stepx = 0;
	data->player.stepy = 0;
	data->player.hit = 0;
	data->player.hit = 0;
	data->player.lineh = 0;
	data->player.drawend = 0;
	data->player.drawstart = 0;
	data->player.prot = 0;
	data->flags.btn_dw = 0;
	data->flags.btn_lt = 0;
}

int					data_constr(t_data *data)
{
	data_constr_2(data);
	data->flags.btn_rt = 0;
	data->flags.btn_up = 0;
	data->flags.rot = 0;
	data->flags.spd = 0;
	data->player.hit = 0;
	data->file.f[0] = -1;
	data->file.f[1] = -1;
	data->file.f[2] = -1;
	data->file.c[0] = -1;
	data->file.c[1] = -1;
	data->file.c[2] = -1;
	data->file.res_ch = 0;
	data->file.c_ch = 0;
	data->file.f_ch = 0;
	data->file.s_ch = 0;
	data->file.no_ch = 0;
	data->file.so_ch = 0;
	data->file.we_ch = 0;
	data->file.ea_ch = 0;
	data->save = 0;
	return (1);
}

int					arg_check(t_data *data, int argc, char **argv)
{
	int	size;
	int	size_save;

	if (argc < 2 || argc > 3)
		error_msg_exit("arg");
	size = ft_strlen(argv[1]);
	if (size < 5)
		error_msg_exit("\".map\"");
	if (argv[1][size - 1] != 'b' || argv[1][size - 2] != 'u'
	|| argv[1][size - 3] != 'c' || argv[1][size - 4] != '.')
		error_msg_exit("\".map\"");
	data->file.fd = open(argv[1], O_RDONLY);
	if (data->file.fd == -1)
		error_msg_exit("\".map\"");
	if (argc > 2)
	{
		size_save = ft_strlen(argv[2]);
		if (ft_strncmp(argv[2], "--save", size_save) == 0 && size_save == 6)
			data->save = 1;
		else
			error_msg_exit("--save");
	}
	return (0);
}

void				init_test(t_data *data, int argc, char **argv)
{
	data_constr(data);
	arg_check(data, argc, argv);
	argv[argc] = NULL;
	if (parser(data) == -1)
		error_msg_exit("Map");
	if (data->file.f[0] == -1 || data->file.f[1] == -1 || data->file.f[2] == -1
	|| data->file.c[0] == -1 || data->file.c[1] == -1 || data->file.c[2] == -1
	|| data->file.resx == -1 || data->file.resy == -1)
		error_msg_exit("Color");
	data->spr_sum = malloc_spr(data);
	data->spritedistance = (double *)malloc(sizeof(double) * data->spr_sum);
	data->spriteorder = (int *)malloc(sizeof(int) * data->spr_sum);
}
