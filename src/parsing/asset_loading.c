/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:41:54 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	rgb_cast(char **spliited_color, char *target);
static int	get_color_component(char *str_value, char *target, char *cname);

/**
 * @brief Load an image asset from the specified line.
 *
 * @param line Array containing the specifier and the path to the image.
 * @param target Pointer to the target image path.
 * @param line_n Line number for error messages.
 *
 * @note Check the target in case of error to understand if the image
 *			has already been loaded before.
 *		 In case of ritght declaration, if the target has already been
 *		 loaded, free it before to allocate a new one.
 *
 * @retval TRUE if the image is loaded successfully.
 * @retval FALSE if something is wrong.
 */
t_bool	load_img(char **line, char **target, int line_n)
{
	int		fd;

	if (ft_count_matrix_row((const void **)line) != 2)
	{
		printe("Invalid %s texture declaration at line %i\n", line[0], line_n);
		if (*target != NULL)
			printe("   Using the previous declaration: [%s]\n", *target);
		return (false);
	}
	fd = open_file(line[1], ".xpm", line[0], line_n);
	if (fd == -1)
		return (false);
	close(fd);
	if (*target != NULL)
		free(*target);
	*target = ft_calloc(ft_strlen(line[1]) + 1, sizeof(char));
	if (!*target)
		return (false);
	ft_strlcpy(*target, line[1], ft_strlen(line[1]) + 1);
	return (true);
}

/**
 * @brief Load a color asset from the specified line.
 *
 * @param line Array containing the specifier and the color value.
 * @param target Pointer to the target color value.
 * @param line_n Line number for error messages.
 *
 * @note Check if there are too many commas, it wouldn't be checked by split
 *			because it's split for ','.
 *		 Check the target in case of error to understand if the color
 *			has already been loaded before.
 *
 * @retval TRUE if the color is loaded successfully.
 * @retval FALSE if something is wrong.
 */
t_bool	load_color(char **line, int *target, int line_n)
{
	char	**splitted_value;
	int		result;

	if (ft_count_matrix_row((const void **)line) != 2
		|| ft_count_occurrences(line[1], ',', 0) != 2)
	{
		printe("Invalid %s color declaration at line %i\n", line[0], line_n);
		if (*target != -1)
			printe("   Using the previous one\n");
		return (false);
	}
	splitted_value = ft_split(line[1], ',');
	result = rgb_cast(splitted_value, line[0]);
	ft_free_matrix((void **)splitted_value);
	if (result == -1)
	{
		if (*target != -1)
			printe("   Using the previous declaration\n");
		return (false);
	}
	*target = result;
	return (true);
}

/**
 * @brief Cast RGB values to an integer.
 *
 * @param splited_color Array containing the RGB values as strings.
 * @param target Target specifier for error messages.
 *
 * @return int The RGB value as an integer.
 * @retval -1 If the RGB values are out of range or invalid.
 */
static int	rgb_cast(char **splited_color, char *target)
{
	int		red;
	int		green;
	int		blue;

	red = get_color_component(splited_color[0], target, "RED");
	green = get_color_component(splited_color[1], target, "GREEN");
	blue = get_color_component(splited_color[2], target, "BLUE");
	return (ft_rgb_to_int(red, green, blue));
}

/**
 * @brief Get the integer value of a color component.
 *
 * @param str_value String containing the color component value.
 * @param target Target specifier for error messages.
 * @param cname Name of the color component for error messages.
 *
 * @note This function is used to check every component of the color.
 *
 * @return int The integer value of the color component.
 * @retval -1 If the value is out of range or invalid.
 */
static int	get_color_component(char *str_value, char *target, char *cname)
{
	int	converted_value;

	converted_value = ft_atoi(str_value);
	if (converted_value < 0 || converted_value > 255
		|| ft_is_string_empty(str_value)
		|| !ft_str_only_contains(str_value, "0123456789"))
	{
		print_color_error(cname, target);
		return (-1);
	}
	return (converted_value);
}
