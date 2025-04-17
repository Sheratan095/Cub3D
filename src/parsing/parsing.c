/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:10 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	read_file(t_vars *vars, int fd);
static t_bool	read_assets(t_vars *vars, int fd);
static t_bool	switch_assets(t_vars *vars, char *line, int line_n, int fd);

/**
 * @brief Retrieves the assets and the map from the specified file.
 *
 * @param vars Pointer to the main struct.
 * @param file Path of the target file.
 *
 * @retval TRUE if the file contains all the assets and the map is valid.
 * @retval FALSE if something is wrong.
 */
t_bool	parse_input_file(t_vars *vars, char *file)
{
	int	fd;

	fd = open_file(file, ".cub", NULL, -1);
	if (fd == -1)
		return (false);
	if (!int_assets(vars))
		return (close(fd), false);
	if (!read_file(vars, fd))
		return (close(fd), false);
	close(fd);
	return (true);
}

/**
 * @brief Reads the file and retrieves the assets and the map.
 *
 * @param vars Pointer to the main struct.
 * @param fd File descriptor of the target file.
 *
 * @retval TRUE if the file contains all the assets and the map is valid.
 * @retval FALSE if something is wrong.
 *
 * @note in case of STRICT_MODE turned off, as long as all the assets
 *			are loaded, the function will return TRUE.
 */
static t_bool	read_file(t_vars *vars, int fd)
{
	t_bool	result;

	result = true;
	if (read_assets(vars, fd) == false)
	{
		if (STRICT_MODE == true)
			result = false;
	}
	get_next_line(fd, true);
	if (all_assets_loaded(vars) == false)
		result = false;
	return (result);
}

/**
 * @brief Reads the assets from the file.
 *
 * @param vars Pointer to the main struct.
 * @param fd File descriptor of the target file.
 *
 * @retval TRUE if the assets are read successfully.
 * @retval FALSE if something is wrong.
 *
 * @note line_count is used just for error messages.
 *		 if (line[0] != '\n') is used to skip empty lines
 *		 trim() free line returned by get_next_line and allocates a new one
 *		 if (line) is used to avoid a double free at the end of the loop
 *			when the last line of the file is read from the map parsing
 */
static t_bool	read_assets(t_vars *vars, int fd)
{
	int		line_count;
	char	*line;
	t_bool	result;

	line_count = 0;
	result = true;
	line = get_next_line(fd, false);
	while (line)
	{
		line_count++;
		if (line[0] != '\n')
		{
			line = ft_strtrim(line, "\n", true);
			if (switch_assets(vars, line, line_count, fd) == false)
				result = false;
		}
		if (line)
			free(line);
		line = get_next_line(fd, false);
	}
	return (result);
}

/**
 * @brief Switches the assets based on the specifier.
 *
 * @param vars Pointer to the main struct.
 * @param line Line containing the specifier and the value.
 * @param line_n Line number. (used just for error messages)
 * @param fd File descriptor of the target file.
 *
 * @retval TRUE if the assets is corrected loaded
 * @retval FALSE if an asset isn't corrected loaded, if the map is invalid
 *				or if the specifier is unknown.
 */
static t_bool	switch_assets(t_vars *vars, char *line, int line_n, int fd)
{
	char	**splitted;
	t_bool	result;

	splitted = ft_split(line, ' ');
	result = false;
	if (ft_strcmp(splitted[0], "NO") == 0)
		result = load_img(splitted, &vars->assets->north_img, line_n);
	else if (ft_strcmp(splitted[0], "SO") == 0)
		result = load_img(splitted, &vars->assets->south_img, line_n);
	else if (ft_strcmp(splitted[0], "WE") == 0)
		result = load_img(splitted, &vars->assets->west_img, line_n);
	else if (ft_strcmp(splitted[0], "EA") == 0)
		result = load_img(splitted, &vars->assets->east_img, line_n);
	else if (ft_strcmp(splitted[0], "C") == 0)
		result = load_color(splitted, &(vars->assets->ceiling_color), line_n);
	else if (ft_strcmp(splitted[0], "F") == 0)
		result = load_color(splitted, &(vars->assets->floor_color), line_n);
	else if (is_start_of_map(line))
		result = load_map(vars, line, fd);
	else
		print_misconfiguration(splitted, line_n);
	return (ft_free_matrix((void **)splitted), result);
}
