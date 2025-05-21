/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 16:07:33 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:07:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	print_error(const char *message, bool return_value)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd((char *)message, 2);
	return (return_value);
}

bool	print_error_with_value(const char *prefix, const char *value,
							bool return_value)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)prefix, 2);
	ft_putendl_fd((char *)value, 2);
	return (return_value);
}
