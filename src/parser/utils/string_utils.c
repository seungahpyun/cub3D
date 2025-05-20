/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 16:12:40 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:12:55 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_handle_char(char *trimmed, int *i, int *j, int *in_space)
{
	if (ft_isspace(trimmed[*i]))
	{
		if (!(*in_space))
		{
			trimmed[(*j)++] = ' ';
			*in_space = 1;
		}
	}
	else
	{
		trimmed[(*j)++] = trimmed[*i];
		*in_space = 0;
	}
	(*i)++;
}

char	*ft_trim_and_compact(char *str)
{
	char	*trimmed;
	int		i;
	int		j;
	int		in_space;

	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	in_space = 0;
	while (trimmed[i])
		ft_handle_char(trimmed, &i, &j, &in_space);
	trimmed[j] = '\0';
	return (trimmed);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
