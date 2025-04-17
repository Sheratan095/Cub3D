/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:41:53 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	normalize_angle(double angle);
static void		move_dir(t_vars *vars, double dir);

void	player_movement(t_vars *vars)
{
	double	dir;

	dir = normalize_angle(atan2(vars->player.dir.y, vars->player.dir.x));
	if (vars->k_right)
		turn(vars, TURNSPEED);
	if (vars->k_left)
		turn(vars, -TURNSPEED);
	if (vars->k_w)
		move_dir(vars, dir);
	if (vars->k_s)
		move_dir(vars, dir + M_PI);
	if (vars->k_a)
		move_dir(vars, dir - M_PI / 2);
	if (vars->k_d)
		move_dir(vars, dir + M_PI / 2);
}

void	turn(t_vars *vars, double tspeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->player.dir.x;
	old_plane_x = vars->player.plane.x;
	vars->player.dir.x = (old_dir_x * cos(tspeed)) \
			- (vars->player.dir.y * sin(tspeed));
	vars->player.dir.y = (old_dir_x * sin(tspeed)) \
			+ (vars->player.dir.y * cos(tspeed));
	vars->player.plane.x = (old_plane_x * cos(tspeed)) \
			- (vars->player.plane.y * sin(tspeed));
	vars->player.plane.y = (old_plane_x * sin(tspeed)) \
			+ (vars->player.plane.y * cos(tspeed));
}

static double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

static void	move_dir(t_vars *vars, double dir)
{
	char	c;
	double	x;
	double	y;

	x = cos(dir) * MOVESPEED;
	y = sin(dir) * MOVESPEED;
	c = vars->map[(int)(vars->player.pos.x + x)][(int)(vars->player.pos.y)];
	if (c == '0' || c == 'O')
		vars->player.pos.x += x;
	c = vars->map[(int)(vars->player.pos.x)][(int)(vars->player.pos.y + y)];
	if (c == '0' || c == 'O')
		vars->player.pos.y += y;
	vars->player.map.x = (int)vars->player.pos.x;
	vars->player.map.y = (int)vars->player.pos.y;
}
