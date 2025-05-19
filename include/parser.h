/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:53 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 10:02:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"

/* element_validator.c */
bool			check_map_extension(const char *filename);
bool			check_texture_path(const char *path);
bool			check_color_value(int r, int g, int b);

/* map_borders_validator.c */
bool			check_map_borders(t_map *map);

/* map_builder.c */
t_list			*create_map_node(char *line);
int				add_first_line(t_list **map_lines, char *first_line);
int				build_map_array(t_map *map, t_list *map_lines);

/* map_closure_validator.c */
bool			validate_map_closure(t_map *map);

/* map_spaces_validator.c */
bool			is_walkable(char c);
bool			check_spaces_surrounded(t_map *map);

/* map_validator.c */
bool			validate_map(t_map *map, t_player *player);

/* parse_elements.c */
int				parse_element(char *line, t_asset *asset);

/* parse_file.c */
int				parse_file(char *filename, t_game *game);

/* parse_map.c */
int				parse_map(int fd, t_game *game, char *first_line);

#endif
