/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:22:46 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/19 23:13:32 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int move_rot(t_data *img, int rot)
{
	if (rot == -1)
		img->player.prot -= (0.1 * (SPEED_ROT / 10));
	if (rot == 1)
		img->player.prot += (0.1 * (SPEED_ROT / 10));
	if (img->player.prot < 0)
		img->player.prot += PI * 2;
	if (img->player.prot > PI * 2)
		img->player.prot -= PI * 2;
	return (1);
}

int	move_up(t_data *img)
{
	int pdx;
	int pdy;

	pdx = cos(img->player.prot) * 3;
	pdy = sin(img->player.prot) * 3;
	img->player.posy += pdy;
	img->player.posx += pdx;
	return (1);
}

int	move_dw(t_data *img)
{
	int pdx;
	int pdy;

	pdx = cos(img->player.prot) * 3;
	pdy = sin(img->player.prot) * 3;
	img->player.posy -= pdy;
	img->player.posx -= pdx;
	return (1);
}

int	move_rt(t_data *img)
{
	int pdx;
	int pdy;

	pdx = cos(img->player.prot) * 3;
	pdy = sin(img->player.prot) * 3;
	img->player.posy += pdy;
	img->player.posx += pdx;
	return (1);
}

int	move_lt(t_data *img)
{
	int pdx;
	int pdy;

	pdx = cos(img->player.prot) * 3;
	pdy = sin(img->player.prot) * 3;
	img->player.posy += pdy;
	img->player.posx += pdx;
	return (1);
}
