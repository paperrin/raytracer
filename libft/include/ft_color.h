/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 19:18:39 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/28 15:23:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

# include "libft.h"
# include "ft_math.h"

typedef struct		s_color_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color_rgb;

typedef struct		s_color_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	float			a;
}					t_color_rgba;

typedef struct		s_color_hsv
{
	unsigned short	h;
	unsigned char	s;
	unsigned char	v;
}					t_color_hsv;

typedef struct		s_color_hsl
{
	unsigned short	h;
	unsigned char	s;
	unsigned char	l;
}					t_color_hsl;

typedef struct		s_clrf_rgb
{
	float			r;
	float			g;
	float			b;
	float			a;
}					t_clrf_rgb;

t_color_rgb			ft_color_rgb(unsigned char r, unsigned char g
		, unsigned char b);
t_color_rgb			ft_color_rgb_add_rgba(t_color_rgb rgb, t_color_rgba rgba);
t_color_rgb			ft_color_rgb_add(t_color_rgb a, t_color_rgb b);
t_color_rgb			ft_color_rgb_scale(t_color_rgb color, double scale);
unsigned int		ft_color_rgb_to_int(t_color_rgb color, int endian);

t_color_rgba		ft_color_rgba(unsigned char r, unsigned char g
		, unsigned char b, float a);

t_color_rgb			ft_color_interpolate(t_color_rgb a, t_color_rgb b, float v);

t_color_hsv			ft_color_hsv(unsigned short h, unsigned char s
		, unsigned char v);

t_color_hsl			ft_color_hsl(unsigned short h, unsigned char s
		, unsigned char l);

t_color_rgb			ft_color_hsv_to_rgb(t_color_hsv hsv);
t_color_rgb			ft_color_rgba_to_rgb(t_color_rgba rgba);

t_clrf_rgb			ft_clrf_rgba(float r, float g, float b, float a);
t_clrf_rgb			ft_clrf_rgb(float r, float g, float b);
t_clrf_rgb			ft_clrf_rgb_clamp(t_clrf_rgb color);
t_color_rgb			ft_clrf_rgb_to_rgb(t_clrf_rgb fcolor);
unsigned int		ft_clrf_rgb_to_int(t_clrf_rgb fl_color, int endian);
t_clrf_rgb			ft_clrf_rgb_add(t_clrf_rgb c1, t_clrf_rgb c2);
t_clrf_rgb			ft_clrf_rgb_sub(t_clrf_rgb c1, t_clrf_rgb c2);
t_clrf_rgb			ft_clrf_rgb_mult(t_clrf_rgb c1, t_clrf_rgb c2);
t_clrf_rgb			ft_clrf_rgb_div(t_clrf_rgb c1, t_clrf_rgb c2);
t_clrf_rgb			ft_clrf_rgb_scale(t_clrf_rgb c, float scale);
t_clrf_rgb			ft_clrf_rgb_div_by(t_clrf_rgb c, float div);

#endif
