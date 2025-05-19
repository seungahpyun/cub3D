/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 16:21:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "common.h"

/* minimap.c */
void			render_minimap(t_game *game);

/* render_utils.c */
bool			is_valid_point(t_game *game, int mx, int my);

#endif
