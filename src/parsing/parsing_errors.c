/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:01:53 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_suggestion(char *identifier, char *target);

/**
 * @brief Prints messages for assets that were not loaded.
 * 
 * @param vars Pointer to the main struct.
 */
void	print_not_loaded_messages(t_vars *vars)
{
	printf("\nNOT LOADED ASSETS:\n");
	if (!vars->assets->north_img)
		printf("    Texture NO not loaded\n");
	if (!vars->assets->south_img)
		printf("    Texture SO not loaded\n");
	if (!vars->assets->west_img)
		printf("    Texture WE not loaded\n");
	if (!vars->assets->east_img)
		printf("    Texture EA not loaded\n");
	if (vars->assets->ceiling_color == -1)
		printf("    Ceiling color not loaded\n");
	if (vars->assets->floor_color == -1)
		printf("    Floor color not loaded\n");
	if (!vars->map)
		printf("    Map not loaded\n");
}

/**
 * @brief Prints a misconfiguration error message and suggestions.
 * 
 * @param line Array containing the identifier at 1° and the value at 2°.
 * @param line_n Line number.
 *
 * @note ft_strncmp with n = 1 used to check only the first char
 *			instead of the whole target to print the suggestion everitime
 *			the string start with the same char and not with the same two char
 *			(it's possible because all the identifiers start
 *			with a different char).
 */
void	print_misconfiguration(char **line, int line_n)
{
	printe("Misconfiguration at line number: %i \n", line_n);
	if (ft_strncmp(line[0], "NO", 1) == 0)
		print_suggestion(line[0], "NO");
	if (ft_strncmp(line[0], "SO", 1) == 0)
		print_suggestion(line[0], "SO");
	if (ft_strncmp(line[0], "WE", 1) == 0)
		print_suggestion(line[0], "WE");
	if (ft_strncmp(line[0], "EA", 1) == 0)
		print_suggestion(line[0], "EA");
	if (ft_strncmp(line[0], "C", 1) == 0)
		print_suggestion(line[0], "C");
	if (ft_strncmp(line[0], "F", 1) == 0)
		print_suggestion(line[0], "F");
}

/**
 * @brief Prints a suggestion for the misconfigured identifier.
 * 
 * @param id Identifier that was misconfigured.
 * @param tgt Target identifier that was expected.
 *
 * @note Just for norminette.
		 First three spaces are for indentation.
 */
static void	print_suggestion(char *id, char *tgt)
{
	printe("   [%s] identifier not recognized, do you mean '%s'?\n", id, tgt);
}

/**
 * @brief Prints an error message with a red color.
 * 
 * @param format Format string for the error message.
 * @param ... Additional arguments for the format string.
 *
 * @return int Number of characters printed.
 *
 * @note Used to print the header (ERROR\n) only once
 *			and to format the result with a indentation.
 *		 Prints in fd 2 (stderr).
 */
int	printe(const char *format, ...)
{
	static t_bool	header_printeed = false;
	va_list			ap;
	int				result;

	va_start(ap, format);
	ft_printf(RED);
	if (!header_printeed)
	{
		ft_printf("ERROR\n");
		header_printeed = true;
	}
	ft_printf("    ");
	result = universal_print(2, format, ap);
	ft_printf(RESET);
	va_end(ap);
	return (result);
}

/**
 * @brief Prints an error message for an out-of-range color component.
 * 
 * @param cname Name of the color component.
 * @param tgt Target identifier.
 *
 * @note Just for norminette.
 */
void	print_color_error(char *cname, char *tgt)
{
	printe("%s component of %s color is out of range (0-255)\n", cname, tgt);
}
