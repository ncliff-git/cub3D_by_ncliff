/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:43:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/19 23:13:15 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480
# define SPEED_ROT 10
# define PI 3.1415926535
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>

typedef struct	s_img
{
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}    			t_img;

typedef struct	s_flag
{
	int			btn_up;
	int			btn_dw;
	int			btn_rt;
	int			btn_lt;
	int			rot;
}				t_flag;

typedef struct	s_player
{
	int			posx;
	int			posy;
	float		prot;
}				t_player;

typedef struct	s_map
{
	int			fd;
	char		*file;
	char		**map;
}				t_map;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_flag		flags;
	t_img		img_pl;
	t_player	player;
}				t_data;

void	cub(t_data *img, int x, int y);
int		map_render(t_data *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		key_press(int keycode, t_data *img);
int		key_realize(int keycode, t_data *img);
int		key_move(t_data *img);
int		move_rot(t_data *img, int rot);
int		move_up(t_data *img);
int		move_dw(t_data *img);
int		move_rt(t_data *img);
int		move_lt(t_data *img);


#endif