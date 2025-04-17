/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:34:49 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check if the file's extension is correct and try to open it.
 *
 * @param file Path of the target file.
 * @param extension Extension that the file must have.
 * @param specifier Specifier for the error message (can be NULL).
 * @param line_n Line number for the error message (can be -1).
 *
 * @note Check the specifier before to print first error message
 *			beacause this function is called without specifier
 *			when trying to open the configuration file (.cub).
 *
 * @return fd File descriptor of the opened file.
 * @retval -1 If something is wrong.
 */
int	open_file(char *file, char *extension, char *specifier, int line_n)
{
	int	fd;

	if (!ft_str_end_with_str(file, extension))
	{
		if (specifier)
			printe("Invalid %s texture at line %i\n   ", specifier, line_n);
		printe("[%s] Wrong file extension, should be %s\n", file, extension);
		return (-1);
	}
	if (ft_file_is_dir(file))
	{
		if (specifier)
			printe("Invalid %s texture at line %i\n   ", specifier, line_n);
		printe("[%s] Is a directory\n", file);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (specifier)
			printe("Invalid %s texture at line %i\n   ", specifier, line_n);
		printe("[%s] Can't open specified file\n", file);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Determine if all assets have been set and
 *			print error messages if not.
 *
 * @param vars Pointer to the main struct.
 *
 * @note int loaded_assets is used to count the number of loaded assets.
 *			and then choose if to print the error messages.
 *		 This function is used combined with print_not_loaded_messages()
 *			to print the header (NOT LOADED ASSETS) only once and just
 *			when there are missing assets.
 *
 * @retval TRUE if all assets have been set.
 * @retval FALSE if some assets are missing.
 */
t_bool	all_assets_loaded(t_vars *vars)
{
	int	loaded_assets;

	loaded_assets = 0;
	if (vars->assets->north_img)
		loaded_assets++;
	if (vars->assets->south_img)
		loaded_assets++;
	if (vars->assets->west_img)
		loaded_assets++;
	if (vars->assets->east_img)
		loaded_assets++;
	if (vars->assets->ceiling_color != -1)
		loaded_assets++;
	if (vars->assets->floor_color != -1)
		loaded_assets++;
	if (vars->map)
		loaded_assets++;
	if (loaded_assets != 7)
		return (print_not_loaded_messages(vars), false);
	return (true);
}

/**
 * @brief Check if the line is the start of the map.
 *
 * @param line Line to check.
 *
 * @note For seplicity, the map start when the line contains only
 *			characters of the MAP_CHARSET, it isn't likely that
 *			another line contains only these characters.
 *
 * @retval TRUE if the line is the start of the map.
 * @retval FALSE if the line is not the start of the map.
 */
t_bool	is_start_of_map(char *line)
{
	return (ft_str_only_contains(line, MAP_CHARSET));
}

/**
 * @brief Get the element at the specified position in the map.
 *
 * @param map The map.
 * @param row_idx Row index.
 * @param col_idx Column index.
 *
 * @note If the indexes are out of bounds, return a space character,
 *			it facilitates the check of the adjacent elements during
 *			the map validation while checking that the map is
 *			surrounded by walls.
 *
 * @return char The element at the specified position in the map.
 */
char	get_map_at(char **map, int row_idx, int col_idx)
{
	int	rows_length;
	int	lines_number;

	if (row_idx < 0 || col_idx < 0)
		return (' ');
	rows_length = ft_strlen(map[row_idx]);
	lines_number = ft_count_matrix_row((const void **)map);
	if (row_idx < 0 || row_idx >= lines_number)
		return (' ');
	if (col_idx < 0 || col_idx >= rows_length)
		return (' ');
	return (map[row_idx][col_idx]);
}

/**
 * @brief Initialize the assets in the main struct.
 *
 * @param vars Pointer to the main struct.
 *
 * @note The colors are initialized to -1 because rgb to int cast
 *			can't return -1.
 *		 It wouldn't work with rgba colors because rgb to int cast
 *			could return valued < 0.
 *
 * @retval TRUE if the assets are initialized successfully.
 * @retval FALSE if there is an error during initialization.
 */
t_bool	int_assets(t_vars *vars)
{
	vars->assets = malloc(sizeof(t_assets));
	if (!vars->assets)
		return (false);
	vars->assets->north_img = NULL;
	vars->assets->south_img = NULL;
	vars->assets->east_img = NULL;
	vars->assets->west_img = NULL;
	vars->assets->ceiling_color = -1;
	vars->assets->floor_color = -1;
	return (true);
}
