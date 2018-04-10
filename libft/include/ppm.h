/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 06:47:05 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 23:19:35 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_H
# define PPM_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "ft_fstream.h"
# include "ft_printf.h"

typedef	struct s_ppm_file	t_ppm_file;
typedef	struct s_depth		t_depth;

struct						s_ppm_file
{
	int						fd;
	char					type;
	size_t					width;
	size_t					height;
	unsigned int			max_val;
	unsigned char			*color_depth_vector;
};

unsigned char				*ft_ppm_file_read(char const *const path,
		size_t *const width, size_t *const height, unsigned int *const max_val);
unsigned char				*ft_ppm_from_floats(t_ppm_file *const file,
							float *ftab);
int							ft_ppm_read_header(t_fstream *file,
		size_t *const width, size_t *const height, unsigned int *const max_val);
int							ft_ppm_file_write(t_ppm_file const *const file);

#endif
