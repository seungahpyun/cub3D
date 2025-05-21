/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_component_parser.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 14:05:27 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/21 15:14:35 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_color_commas(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}

int	check_extra_color_chars(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (-1);
		str++;
	}
	return (0);
}

static void	handle_sign(char **str, bool *negative)
{
	*negative = false;
	if (**str == '-')
	{
		*negative = true;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
}

int	parse_color_component(char **str, int *value)
{
	int		j;
	bool	negative;
	bool	has_digit;

	has_digit = false;
	while (**str && (**str == ' ' || **str == ','))
		(*str)++;
	handle_sign(str, &negative);
	j = 0;
	*value = 0;
	while (**str && ft_isdigit(**str))
	{
		*value = *value * 10 + (**str - '0');
		(*str)++;
		j++;
		has_digit = true;
	}
	if (!has_digit)
		return (0);
	if (negative)
		*value = -*value;
	return (j);
}
