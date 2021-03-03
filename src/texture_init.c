/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:22:51 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int					mlx_texture_2(t_data *data)
{
	if (!(data->ea_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.ea_ture,
	&data->ea_tx.sp_x, &data->ea_tx.sp_y)))
		error_msg_exit("Texture");
	data->ea_tx.addr = mlx_get_data_addr(data->ea_tx.img,
	&data->ea_tx.bits_per_pixel, &data->ea_tx.line_length, &data->ea_tx.endian);
	data->s_tx.img = mlx_new_image(data->mlx, TEX_WH, TEX_HEIGHT);
	if (!(data->s_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.s_ture,
	&data->s_tx.sp_x, &data->s_tx.sp_y)))
		error_msg_exit("Sprite");
	data->s_tx.addr = mlx_get_data_addr(data->s_tx.img,
	&data->s_tx.bits_per_pixel, &data->s_tx.line_length, &data->s_tx.endian);
	return (1);
}

int							mlx_texture(t_data *data)
{
	data->no_tx.img = mlx_new_image(data->mlx, TEX_WH, TEX_HEIGHT);
	if (!(data->no_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.no_ture,
	&data->no_tx.sp_x, &data->no_tx.sp_y)))
		error_msg_exit("Texture");
	data->no_tx.addr = mlx_get_data_addr(data->no_tx.img,
	&data->no_tx.bits_per_pixel, &data->no_tx.line_length, &data->no_tx.endian);
	data->so_tx.img = mlx_new_image(data->mlx, TEX_WH, TEX_HEIGHT);
	if (!(data->so_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.so_ture,
	&data->so_tx.sp_x, &data->so_tx.sp_y)))
		error_msg_exit("Texture");
	data->so_tx.addr = mlx_get_data_addr(data->so_tx.img,
	&data->so_tx.bits_per_pixel, &data->so_tx.line_length, &data->so_tx.endian);
	data->we_tx.img = mlx_new_image(data->mlx, TEX_WH, TEX_HEIGHT);
	if (!(data->we_tx.img = mlx_xpm_file_to_image(data->mlx, data->file.we_ture,
	&data->we_tx.sp_x, &data->we_tx.sp_y)))
		error_msg_exit("Texture");
	data->we_tx.addr = mlx_get_data_addr(data->we_tx.img,
	&data->we_tx.bits_per_pixel, &data->we_tx.line_length, &data->we_tx.endian);
	data->ea_tx.img = mlx_new_image(data->mlx, TEX_WH, TEX_HEIGHT);
	mlx_texture_2(data);
	return (1);
}
