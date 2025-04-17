/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:32:39 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// possible components of the map
# define MAP_CHARSET "01 NSEW"
# define MAP_CHARSET_BONUS "01 NSEWD"

# ifndef STRICT_MODE
#  define STRICT_MODE 1
# endif

# define MAP_MAX_WIDTH 240

# define MAP_MAX_HEIGHT 135

# include "cub3D.h"

// Forward Declaration
typedef struct s_vars	t_vars;

typedef struct s_assets
{
	char	*north_img;
	char	*south_img;
	char	*west_img;
	char	*east_img;

	int		ceiling_color;
	int		floor_color;

}	t_assets;

t_bool	parse_input_file(t_vars *vars, char *file);

t_bool	all_assets_loaded(t_vars *vars);

int		open_file(char *file, char *extension, char *specifier, int line_n);

t_bool	load_img(char **line, char **target, int line_n);

t_bool	load_color(char **line, int *target, int line_n);

t_bool	load_map(t_vars *vars, char *line, int fd);

t_bool	is_start_of_map(char *line);

t_bool	int_assets(t_vars *vars);

char	get_map_at(char **map, int row_idx, int col_idx);

int		printe(const char *format, ...);

void	print_color_error(char *cname, char *tgt);

void	print_misconfiguration(char **line, int line_n);

void	print_not_loaded_messages(t_vars *vars);

#endif
