/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 20:25:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 20:26:48 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_frame_count(int count)
{
	return (count >= MIN_SPRITE_FRAMES && count <= MAX_SPRITE_FRAMES);
}
