/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:30:41 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_vars	*init_vars( void );
static t_data	new_data( void );

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = init_vars();
	ft_printf("STRICT MODE: %i\n", STRICT_MODE);
	if (argc != 2)
		return (printf("Error\nWrong number of parameters\n"), 1);
	if (!parse_input_file(vars, argv[1]))
	{
		cleanup(vars);
		return (1);
	}
	printf(GREEN"\nALL ASSETS ARE LOADED CORRECTLY\n"RESET);
	printf(GREEN"STARTING GAME...\n"RESET);
	init_game(vars);
}

// 4 is both the number of sprites and the number of directions
static t_vars	*init_vars( void )
{
	int		i;
	t_vars	*vars;

	i = 0;
	vars = malloc(sizeof(t_vars));
	vars->assets = NULL;
	vars->map = NULL;
	vars->mlx = NULL;
	vars->mlx_win = NULL;
	vars->door = new_data();
	while (i < 4)
	{
		vars->img[i] = new_data();
		vars->gui[i] = new_data();
		i++;
	}
	return (vars);
}

static t_data	new_data( void )
{
	t_data	data;

	data.img = NULL;
	data.addr = NULL;
	data.path = NULL;
	data.bits_per_pixel = 0;
	data.line_length = 0;
	data.endian = 0;
	data.width = 0;
	data.height = 0;
	return (data);
}
