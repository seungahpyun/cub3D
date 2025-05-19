/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 09:45:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "common.h"

/* minimap.c */
bool			is_valid_point(t_game *game, int mx, int my);
void			render_minimap(t_game *game);

#endif
