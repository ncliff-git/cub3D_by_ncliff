/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:43:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/25 21:37:08 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# define SPEED_MOVE 0.07
# define SHIFT_MOVE 2
# define CTRL_MOVE -1
# define SPEED_ROT 0.05
# define PI 3.1415926535
# define PI2 PI/2
# define PI3 PI/3

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
	float		spd;
}				t_flag;

/*
** posx, posy - позиция игрока по x и y
** dirx, diry - начальный вектор направления.
** planx, plany - плоскость плана.
** camx - камера по x направлению.
** raydirx, raydiry - направление луча.
** mapx, mapy - текущий квадрат карты, в которой находится луч.
** sdistx, sdisty - начальное растояние до границ клетки.
** ddistx, ddisty - от начальной границы до сл.гр..
** pwdist - длина луча.
** stepx, stepy - направление шага
** hit - наличие стены.
** side - сторона.
*/
typedef struct	s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		cam;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sdistx;
	double		sdisty;
	double		ddistx;
	double		ddisty;
	double		pwdist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineh;
	int			drawstart;
	int			drawend;
	float		prot;
}				t_player;

typedef struct	s_map
{
	int			fd;
	t_list		*file;
	int			resx;
	int			resy;
	int			szx;
	int			szy;
	char		**map;
}				t_map;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		img_mmp;
	t_img		img_mp;
	t_img		img_pl;
	t_player	player;
	t_flag		flags;
	t_map		file;
}				t_data;

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				key_press(int keycode, t_data *img);
int				key_realize(int keycode, t_data *img);
int				key_move(t_data *img);
int				move_rot(t_data *img, int rot);
int				move_up(t_data *img);
int				move_dw(t_data *img);
int				move_rt(t_data *img);
int				move_lt(t_data *img);

int				drowline(int x, int colorR, t_data *data);

int				parser(t_data *data);
int				pars_r(t_data *data, char *line);


#endif