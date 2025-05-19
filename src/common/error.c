/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 16:57:05 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/19 09:48:58 by spyun         ########   odam.nl         */
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
