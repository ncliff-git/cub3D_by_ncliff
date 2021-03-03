/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:56:00 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	create_screen(t_data *all, int fd)
{
	int		size_screen;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	size_screen = all->file.resx * all->file.resy * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &all->file.resx, 4);
	write(fd, &all->file.resy, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

static void	filling_file_screen(t_data *all, int fd)
{
	int	i;
	int	j;
	int	color;

	i = all->file.resy;
	while (--i >= 0)
	{
		j = -1;
		while (++j < all->file.resx)
		{
			color = *(int*)(all->img_mp.addr + (i * all->img_mp.line_length
					+ j * (all->img_mp.bits_per_pixel / 8)));
			write(fd, &color, 4);
		}
	}
}

void		screenshot(t_data *all)
{
	int fd;
	int size_screen;
	int zero;
	int size;

	if ((fd = open("screen.bmp", O_CREAT | O_RDWR, 0666)) < 0)
		error_msg_exit("Error\n in fd screenshot\n‿︵‿ヽ(°□° )ノ︵‿︵\n");
	size_screen = all->file.resx * all->file.resy * 4 + 54;
	zero = 0;
	size = all->file.resx * all->file.resy;
	create_screen(all, fd);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	size_screen = 1000;
	write(fd, &size_screen, 4);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	filling_file_screen(all, fd);
	close(fd);
}
