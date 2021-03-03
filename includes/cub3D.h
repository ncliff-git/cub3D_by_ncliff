/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:43:04 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 21:17:22 by ncliff           ###   ########.fr       */
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
# define TEX_WH 256
# define TEX_HEIGHT 256

/*
** структура холстов
*/
typedef struct		s_img
{
	void			*img;
	void			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				sp_x;
	int				sp_y;
}					t_img;

/*
** флаги нажатия кнопок для возможности зажать несколько кнопок
*/
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
** side - сторона стены.
** lineh - высота стены.
** drawstart, drawend - начало и конец рисования.
** prot - направление игрока.
** wall_x -
** tex_x, tex_y -
** tex_pos -
** step -
** sprite_x, sprite_y -
** inv_det -
** tran_x, tran_y -
** spr_scr_x -
** spr_height -
** spr_widht -
** dr_st_sp_y, dr_nd_sp_y -
** dr_st_sp_x, dr_nd_sp_x -
** sp_tex_x, sp_tex_y -
** color_sp -
*/
typedef struct		s_player
{
	int				h;
	int				w;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			cam;
	double			rdirx;
	double			rdiry;
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
	int				tex_y;
	double			tex_pos;
	double			step;
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

/*
** fd -
** *file -
** resx -
** resy -
** *no_ture -
** *so_ture -
** *we_ture -
** *ea_ture -
** *s_ture -
** f -
** c -
** szx -
** szy -
** stpos -
** **map -
** res_ch -
** c_ch -
** f_ch -
** we_ch -
** ea_ch -
** no_ch -
** so_ch -
** s_ch -
*/
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
	int				res_ch;
	int				c_ch;
	int				f_ch;
	int				we_ch;
	int				ea_ch;
	int				no_ch;
	int				so_ch;
	int				s_ch;
}					t_map;

/*
** posx -
** posy -
** dist -
** *next -
*/
typedef struct		s_spr
{
	float			posx;
	float			posy;
	double			dist;
	struct s_spr	*next;
}					t_spr;

/*
** *mlx -
** *mlx_win -
** img_mmp -
** img_mp -
** img_pl -
** no_tx -
** so_tx -
** we_tx -
** ea_tx -
** s_tx -
** *spr -
** spr_sum -
** *spriteorder -
** *spritedistance -
** player -
** flags -
** file -
** save -
** map_check -
*/
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
	int				*spriteorder;
	double			*spritedistance;
	t_player		player;
	t_flag			flags;
	t_map			file;
	int				save;
	int				map_check;
}					t_data;

/*
** структура для сортировуи спрайтов
*/
typedef struct		s_pair
{
	double			first;
	int				second;
}					t_pair;

int					mlx_texture(t_data *data);
int					create_trgb(int t, int r, int g, int b);
void				pixel_put(t_img *img, int x, int y, int color);
unsigned int		pixel_take(t_img *img, int x, int y);
int					key_press(int keycode, t_data *img);
int					key_realize(int keycode, t_data *img);
int					key_move(t_data *img);
int					move_rot(t_data *data, int rot);
int					move_up(t_data *data);
int					move_dw(t_data *data);
int					move_rt(t_data *data);
int					move_lt(t_data *data);
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
int					rendersky(t_data *data);
void				ray_math(t_data *data, t_player *pl, int x);
void				dda_math(t_data *data, t_player *pl);
void				wall_side(t_data *data, t_player *pl);
void				render_wall(t_data *data, int x);
void				sort_sp(t_data *data);
void				sp_math(t_data *data, t_player *pl, int i);
void				render_sp(t_data *data, t_player *pl, double **z_b);
void				error_msg_exit(char *str);
void				screenshot(t_data *all);
void				valid_param_2(t_data *data, char ch, char ch2);
int					pars1_dop(t_data *data, t_list *first, int res);
int					exit_funk(t_data *img);
void				init_test(t_data *data, int argc, char **argv);
void				sort_sprites(int *order, double *dist, int amount);

#endif
