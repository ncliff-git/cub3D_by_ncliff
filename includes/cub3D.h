/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:43:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/21 20:39:20 by ncliff           ###   ########.fr       */
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
# define WORLD_MAP data->file.map
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define RES_X data->file.resx
# define RES_Y data->file.resy
# define P_CAM data->player.cam
# define PLAN_X data->player.planx
# define PLAN_Y data->player.plany
# define DIR_X data->player.dirx
# define DIR_Y data->player.diry
# define P_MAP_X data->player.mapx
# define P_MAP_Y data->player.mapy
# define R_DIR_X data->player.raydirx
# define R_DIR_Y data->player.raydiry
# define D_DIST_X data->player.ddistx
# define D_DIST_Y data->player.ddisty
# define STEP_X data->player.stepx
# define STEP_Y data->player.stepy
# define S_DIST_X data->player.sdistx
# define S_DIST_Y data->player.sdisty
# define POS_X data->player.posx
# define POS_Y data->player.posy
# define PW_DIST data->player.pwdist
# define SIDE data->player.side
# define HIT data->player.hit
# define LINE_H data->player.lineh
# define DR_START data->player.drawstart
# define DR_END data->player.drawend

# define SP_X data->player.sprite_x
# define SP_Y data->player.sprite_y
# define INV_DET data->player.inv_det
# define TRAN_X data->player.tran_x
# define TRAN_Y data->player.tran_y
# define SPR_SCR_X data->player.spr_scr_x
# define SPR_HT data->player.spr_height
# define SPR_WT data->player.spr_widht
# define DR_SP_ST_Y data->player.dr_st_sp_y
# define DR_SP_ND_Y data->player.dr_nd_sp_y
# define DR_SP_ST_X data->player.dr_st_sp_x
# define DR_SP_ND_X data->player.dr_nd_sp_x
# define SP_TEX_X data->player.sp_tex_x
# define SP_TEX_Y data->player.sp_tex_y
# define SP_CR data->player.color_sp
# define WALL_X data->player.wall_x
# define TEX_X data->player.tex_x
# define TEX_Y data->player.tex_y
# define STEP data->player.step
# define TEX_POS data->player.tex_pos
# define SPR_ORD data->spriteOrder
# define SPR_DST data->spriteDistance

typedef struct		s_img
{
	void			*img;
	void			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_flag
{
	int				btn_up;
	int				btn_dw;
	int				btn_rt;
	int				btn_lt;
	int				rot;
	float			spd;
}					t_flag;

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
typedef struct		s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			cam;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sdistx;
	double			sdisty;
	double			ddistx;
	double			ddisty;
	double			pwdist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineh;
	int				drawstart;
	int				drawend;
	float			prot;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			tran_x;
	double			tran_y;
	int				spr_scr_x;
	int				spr_height;
	int				spr_widht;
	int				dr_st_sp_y;
	int				dr_nd_sp_y;
	int				dr_st_sp_x;
	int				dr_nd_sp_x;
	int				sp_tex_x;
	int				sp_tex_y;
	int				color_sp;
}					t_player;

typedef struct		s_map
{
	int				fd;
	t_list			*file;
	int				resx;
	int				resy;
	char			*no_ture;
	char			*so_ture;
	char			*we_ture;
	char			*ea_ture;
	char			*s_ture;
	int				f[3];
	int				c[3];
	int				szx;
	int				szy;
	char			stpos;
	char			**map;
}					t_map;

typedef struct		s_spr
{
	float			posx;
	float			posy;
	double			dist;
	struct s_spr	*next;
}					t_spr;

typedef struct		s_data
{
	void			*mlx;
	void			*mlx_win;
	t_img			img_mmp;
	t_img			img_mp;
	t_img			img_pl;
	t_img			no_tx;
	t_img			so_tx;
	t_img			we_tx;
	t_img			ea_tx;
	t_img			s_tx;
	t_spr			*spr;
	int				spr_sum;
	int				*spriteOrder;
	double			*spriteDistance;
	t_player		player;
	t_flag			flags;
	t_map			file;
}					t_data;

/////////////////////////////////////////////////


typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

/////////////////////////////////////////////////

void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int		my_mlx_pixel_take(t_img *img, int x, int y);
int					key_press(int keycode, t_data *img);
int					key_realize(int keycode, t_data *img);
int					key_move(t_data *img);
int					move_rot(t_data *img, int rot);
int					move_up(t_data *img);
int					move_dw(t_data *img);
int					move_rt(t_data *img);
int					move_lt(t_data *img);
int					drowline(int x, int colorr, t_data *data);
int					parser(t_data *data);
int					pars_res(t_data *data, char *line);
int					pars_map(t_data *data);
int					valid_map(t_data *data);
int					pars_texture(char **texture, char s, char *line);
int					pars_color(int *data, char *line);

t_spr				*sprlstnew(float posx, float posy, double dist);
void				sprlstadd_back(t_spr **lst, t_spr *new);
int					malloc_spr(t_data *data);
double				get_spr(t_spr *data, int i, int ch);

/////////////////////////////////////////////////

void				sortSprites(int *order, double *dist, int amount);

/////////////////////////////////////////////////


#endif
