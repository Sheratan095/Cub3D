/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:38:03 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// button1 is left click
int	click_hanlder(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 1)
		vars->mouse_clicked = 1;
	return (0);
}

//mouse movement
int	mouse_handler(int x, int y, t_vars *vars)
{
	(void)y;
	mlx_mouse_move(vars->mlx, vars->mlx_win, SCREEN_W / 2, SCREEN_H / 2);
	if (x > SCREEN_W / 2)
		turn(vars, TURNSPEED);
	else if (x < SCREEN_W / 2)
		turn(vars, -TURNSPEED);
	return (0);
}
