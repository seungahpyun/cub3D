/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 16:57:05 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/26 12:09:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ft_mlx_error(t_game *game)
{
	char	*error_msg;

	error_msg = (char *)mlx_strerror(mlx_errno);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free_game(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(EXIT_FAILURE);
}

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
