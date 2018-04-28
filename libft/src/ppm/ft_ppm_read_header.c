/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:11:15 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/28 19:58:32 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ppm.h"

static size_t	read_size(char **line)
{
	size_t		size;

	if (!ft_isdigit((int)**line))
		return (0);
	size = ft_atoi(*line);
	while (ft_isdigit((int)**line))
		(*line)++;
	return (size);
}

static size_t	read_max_val(char **line)
{
	size_t	max_val;

	max_val = read_size(line);
	if (max_val < 1 || max_val > 65535)
		return (0);
	return (max_val);
}

static int		skip_comment(t_fstream *const file, char **line)
{
	char	*new_line;
	int		ret;

	if (**line != '#')
		return (0);
	new_line = ft_strchr_any(*line, "\n\r");
	if (!new_line)
	{
		ft_strdel(line);
		if ((ret = ft_fstream_sread_to_any_char(file, line, "\r\n", 1)) <= 0)
			return (0);
	}
	ft_strdel(line);
	if ((ret = ft_fstream_sread_to_any_char(file, line, "\v\f\n\t\r ", 1)) <= 0)
		return (0);
	return (1);
}

int				ft_ppm_read_header(t_fstream *const file, size_t *const width,
		size_t *const height, unsigned int *const max_val)
{
	static char		*prev_line = NULL;
	int				ret;
	char			*line;
	int				token;

	token = 0;
	while (token != 4 && (ret = ft_fstream_sread_to_any_char(
					file, &line, "\v\f\n\t\r ", 1)) > 0)
	{
		ft_strdel(&prev_line);
		prev_line = line;
		if (ft_is_whitespace((int)*line))
			continue ;
		if (*line == '#' && !skip_comment(file, &line))
			break ;
		prev_line = line;
		if ((token == 0 && (ft_strstr(line, "P6") == line) && ++token)
			|| (token == 1 && (*width = read_size(&line)) && ++token)
			|| (token == 2 && (*height = read_size(&line)) && ++token)
			|| (token == 3 && (*max_val = read_max_val(&line)) && ++token))
			continue ;
		break ;
	}
	ft_strdel(&prev_line);
	return (token == 4 && ret > 0);
}
