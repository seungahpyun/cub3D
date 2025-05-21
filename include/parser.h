/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:53 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/21 15:11:24 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"

/* ========================================================================== */
/*                             ELEMENT PARSING                                */
/* ========================================================================== */
/* color_component_parser.c */
int				count_color_commas(const char *str);
int				check_extra_color_chars(char *str);
int				parse_color_component(char **str, int *value);
/* color_parser.c */
int				parse_color_value(char *line, t_color *color);
/* element_checker.c */
bool			check_texture_path(const char *path);
bool			check_color_value(int r, int g, int b);
bool			check_all_elements_set(t_asset *asset);
/* element_parser.c */
int				parse_element(char *line, t_asset *asset);
/* texture_parser.c */
bool			check_texture_extension(const char *path);
int				parse_texture_path(char *line, char **path);
/* ========================================================================== */
/*                               FILE PARSING                                 */
/* ========================================================================== */
/* file_content.c */
int				parse_map_content(t_game *game, int fd, int ret);
/* file_parser.c */
int				parse_file(char *filename, t_game *game);
int				parse_map(int fd, t_game *game, char *first_line);
/* file_processor.c */
int				process_line(char *line, t_game *game, int fd);
int				check_content_after_map(int fd);
int				check_map_file(t_game *game, bool map_found);
/* ========================================================================== */
/*                               MAP PARSING                                  */
/* ========================================================================== */
/* map_borders.c */
bool			check_map_borders(t_map *map);
/* map_builder.c */
t_list			*create_map_node(char *line);
int				add_first_line(t_list **map_lines, char *first_line);
int				build_map_array(t_map *map, t_list *map_lines);
/* map_checker.c */
bool			validate_map_content(t_map *map, t_player *player);
bool			check_map_extension(const char *filename);
/* map_closure.c */
bool			check_surrounding_walls(t_map *map);
/* map_loader.c */
int				read_map_lines(int fd, t_list **map_lines, char *first_line);
bool			has_valid_first_line(char *line);
/* map_spaces.c */
bool			check_spaces_surrounded(t_map *map);
/* map_validator.c */
bool			validate_map(t_map *map, t_player *player);
bool			validate_map_closure(t_map *map);
/* ========================================================================== */
/*                               UTILITY FUNCTIONS                            */
/* ========================================================================== */
/* error_utils.c */
bool			print_error(const char *message, bool return_value);
bool			print_error_with_value(const char *prefix, const char *value,
					bool return_value);
/* file_utils.c */
bool			check_file_extension(const char *path, const char *extension);
void			gnl_cleanup(int fd);
/* string_utils.c */
char			*ft_trim_and_compact(char *str);
bool			is_empty_line(char *line);
/* map_utils.c */
bool			is_valid_position(int x, int y, int height, int width);
bool			is_walkable(char c);
bool			is_map_char(char c);

#endif
