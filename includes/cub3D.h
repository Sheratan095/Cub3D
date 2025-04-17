/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:23:43 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:32 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "corekit.h"
# include "parsing.h"

# define TEX_SIZE		128
# define SCREEN_W		1920
# define SCREEN_H		1080
# define TURNSPEED		0.05
# define FOV			60
# define MOVESPEED		0.1
# define WALL			'1'
# define FLOOR			'0'
# define PLAYER			'P'
# define TILE_SIZE		8
# define DESTROY_NOTIFY 17
# define KEY_SPACE		32
# define KEY_ESC		65307
# define W_KEY			119
# define R_KEY			114
# define A_KEY			97
# define S_KEY			115
# define D_KEY			100
# define E_KEY			101
# define UP_ARROW		65362
# define LEFT_ARROW		65361
# define DOWN_ARROW		65364
# define RIGHT_ARROW	65363
# define WHITE			0x00FFFFFF
# define BLACK			0x00000000
# define YELLOW			0x00FFFF00
# define CYAN			0x0000FFFF
# define MAGENTA		0x00FF00FF
# define ORANGE			0x00FFA500
# define PURPLE			0x008A2BE2

# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define BLUE			"\033[34m"
# define RESET			"\033[0m"

# define POINTER_COLOR	0x00FFFFFF

# ifndef BONUS
#  define BONUS 0
# endif

// Forward Declaration
typedef struct s_assets	t_assets;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_player
{
	t_point		pos;
	t_point		dir;
	t_point		map;
	t_point		plane;
}				t_player;

typedef struct s_ray
{
	int		index;
	double	camerax;
	double	wall_x;
	t_point	dir;
	t_point	d_dist;
	t_point	s_dist;
	t_point	pos;
	t_point	step;
	t_point	map;
	int		hit;
	int		side;
	double	distance;
	int		flag;

	t_bool	is_door;
}				t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	char	*path;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct s_vars
{
	// char		*error_msg;	// DEPRECATED
	void		*mlx;
	void		*mlx_win;

	char		**map;

	int			mouse_clicked;

	int			frame_count;

	t_bool		looking_at_door;
	t_point		door_looking_at;
	double		door_dist;

	int			k_a;
	int			k_w;
	int			k_s;
	int			k_d;
	int			k_left;
	int			k_right;
	int			number_of_rows;
	int			number_of_columns;

	t_data		door;
	t_data		gui[4];
	t_data		img[4];
	t_data		*data;
	t_player	player;
	t_ray		ray;
	t_assets	*assets;
}				t_vars;

void		display_door_suggestions(t_vars *vars);

void		init_game(t_vars *vars);

void		digital_differential_analyser(t_vars *vars, t_ray *ray);

void		raycast(t_vars *vars);

int			display(t_vars *vars);

int			hook(t_vars *vars);

int			mouse_handler(int x, int y, t_vars *vars);

int			click_hanlder(int button, int x, int y, t_vars *vars);

void		hanlde_e_press(t_vars *vars);

void		render_minimap(t_vars *vars);

void		render_gui(t_vars *vars);

t_player	initiate_player(t_vars *vars, t_point player);

void		player_movement(t_vars *vars);

void		turn(t_vars *vars, double tspeed);

t_point		find_player(t_vars *vars);

void		cleanup(t_vars *vars);

int			closemlx(t_vars *vars);

void		circle_bres(int xc, int yc, int r, t_vars *vars);

void		draw_column(t_vars *vars, int x);

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

char		*get_pixel_address(t_data *data, int x, int y);

void		render_square(int x, int y, t_vars *vars, int color);

void		draw_border(int x, int y, t_vars *vars, int color);

#endif
