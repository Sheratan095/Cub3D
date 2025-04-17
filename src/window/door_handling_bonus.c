/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:51:34 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	is_door_near_player(t_vars *vars);
static void		display_message(t_vars *vars, char *message);

void	display_door_suggestions(t_vars *vars)
{
	t_point	looking_at;

	if (vars->looking_at_door && is_door_near_player(vars))
	{
		looking_at = vars->door_looking_at;
		if (vars->map[(int) looking_at.x][(int) looking_at.y] == 'D')
			display_message(vars, "Press E to open the door");
		else if (vars->map[(int) looking_at.x][(int) looking_at.y] == 'O')
			display_message(vars, "Press E to close the door");
	}
}

void	hanlde_e_press(t_vars *vars)
{
	t_point	door;

	if (vars->player.map.x == vars->door_looking_at.x
		&& vars->player.map.y == vars->door_looking_at.y)
		return ;
	if (vars->looking_at_door && is_door_near_player(vars))
	{
		door = vars->door_looking_at;
		if (vars->map[(int)door.x][(int)door.y] == 'D')
			vars->map[(int)door.x][(int)door.y] = 'O';
		else if (vars->map[(int)door.x][(int)door.y] == 'O')
			vars->map[(int)door.x][(int)door.y] = 'D';
	}
}

static void	display_message(t_vars *vars, char *message)
{
	int	x;
	int	y;

	x = SCREEN_W / 2 - (ft_strlen(message) * 5);
	y = SCREEN_H / 2 + 20;
	mlx_string_put(vars->mlx, vars->mlx_win, x, y, 0xFFFFFF, message);
}

static t_bool	is_door_near_player(t_vars *vars)
{
	if (vars->player.map.x == vars->door_looking_at.x
		&& vars->player.map.y == vars->door_looking_at.y)
		return (0);
	return (vars->door_dist <= 1.2);
}
