/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:17:25 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:29:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "libft.h"
# include <math.h>

# define MATH_MX_SIZE 4

typedef struct	s_vec2i
{
	int		x;
	int		y;
}				t_vec2i;

typedef struct	s_vec2d
{
	double	x;
	double	y;
}				t_vec2d;

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

typedef struct	s_vec3f
{
	float	x;
	float	y;
	float	z;
}				t_vec3f;

typedef struct	s_vec3d
{
	double	x;
	double	y;
	double	z;
}				t_vec3d;

typedef struct	s_vec3ld
{
	long double		x;
	long double		y;
	long double		z;
}				t_vec3ld;

typedef struct	s_matrix
{
	float	m[MATH_MX_SIZE * MATH_MX_SIZE];
}				t_matrix;

t_matrix		*ft_matrix_new(void);
t_matrix		*ft_matrix_copy(t_matrix *dst, t_matrix const *const src);
void			ft_matrix_del(t_matrix **mx);
void			ft_matrix_to_identity(t_matrix *const mx);
void			ft_matrix_multiply(t_matrix *dest, t_matrix const *const a
		, t_matrix const *const b);
void			ft_matrix_translate(t_matrix *mx, float x, float y, float z);
void			ft_matrix_scale(t_matrix *mx, float x, float y, float z);
void			ft_matrix_rot(t_matrix *mx, float x, float y, float z);
void			ft_matrix_rot_x(t_matrix *mx, float alpha);
void			ft_matrix_rot_y(t_matrix *mx, float alpha);
void			ft_matrix_rot_z(t_matrix *mx, float alpha);
void			ft_matrix_rot_axis(t_matrix *const mx, t_vec3f axis
		, float alpha);

t_vec3f			ft_vec3f(float x, float y, float z);
t_vec3f			*ft_vec3f_new(float x, float y, float z);
t_vec3f			ft_vec3f_transform(t_vec3f const *const vec
		, t_matrix const *const mx);
t_vec3f			ft_vec3f_add(t_vec3f a, t_vec3f b);
t_vec3f			ft_vec3f_sub(t_vec3f a, t_vec3f b);
t_vec3f			ft_vec3f_mult(t_vec3f a, t_vec3f b);
float			ft_vec3f_mag(t_vec3f vec);
float			ft_vec3f_dot(t_vec3f a, t_vec3f b);
t_vec3f			ft_vec3f_norm(t_vec3f vec);
t_vec3f			ft_vec3f_rot_x(t_vec3f vec, float angle);
t_vec3f			ft_vec3f_rot_y(t_vec3f vec, float angle);
t_vec3f			ft_vec3f_rot_z(t_vec3f vec, float angle);
t_vec3f			ft_vec3f_rot(t_vec3f vec, float x, float y, float z);
t_vec3f			ft_vec3f_scale(t_vec3f vec, float scale);
t_vec3f			ft_vec3f_matrix_rot(t_vec3f const *const vec
		, t_matrix const *const mx);

t_vec3d			ft_vec3d(double x, double y, double z);
t_vec3d			*ft_vec3d_new(double x, double y, double z);
t_vec3d			ft_vec3d_add(t_vec3d a, t_vec3d b);
t_vec3d			ft_vec3d_sub(t_vec3d a, t_vec3d b);
t_vec3d			ft_vec3d_mult(t_vec3d a, t_vec3d b);
t_vec3d			ft_vec3d_cross(t_vec3d a, t_vec3d b);
double			ft_vec3d_mag(t_vec3d vec);
double			ft_vec3d_dot(t_vec3d a, t_vec3d b);
t_vec3d			ft_vec3d_norm(t_vec3d vec);
t_vec3d			ft_vec3d_rot_x(t_vec3d vec, double angle);
t_vec3d			ft_vec3d_rot_y(t_vec3d vec, double angle);
t_vec3d			ft_vec3d_rot_z(t_vec3d vec, double angle);
t_vec3d			ft_vec3d_rot(t_vec3d vec, double x, double y, double z);
t_vec3d			ft_vec3d_scale(t_vec3d vec, double scale);
t_vec3d			ft_vec3d_div_by(t_vec3d vec, double scale);

t_vec3ld		ft_vec3ld(long double x, long double y, long double z);
t_vec3ld		*ft_vec3ld_new(long double x, long double y, long double z);

t_vec2i			ft_vec2i(int x, int y);
t_vec2i			*ft_vec2i_new(int x, int y);
t_vec2i			ft_vec2i_transform(t_vec2i const *const vec
		, t_matrix const *const mx);

t_vec2d			ft_vec2d(double x, double y);
t_vec2d			*ft_vec2d_new(double x, double y);

t_vec2f			ft_vec2f(float x, float y);
t_vec2f			*ft_vec2f_new(float x, float y);
t_vec2f			ft_vec2f_add(t_vec2f a, t_vec2f b);
t_vec2f			ft_vec2f_sub(t_vec2f a, t_vec2f b);
t_vec2f			ft_vec2f_mult(t_vec2f a, t_vec2f b);
float			ft_vec2f_mag(t_vec2f vec);
float			ft_vec2f_dot(t_vec2f a, t_vec2f b);
t_vec2f			ft_vec2f_rot(t_vec2f vec, float angle);
t_vec2f			ft_vec2f_scale(t_vec2f vec, float scale);

long double		ft_minf(long double a, long double b);
long double		ft_maxf(long double a, long double b);
long double		ft_clampf(long double val, long double min, long double max);
long double		ft_absf(long double val);
intmax_t		ft_min(intmax_t a, intmax_t b);
intmax_t		ft_max(intmax_t a, intmax_t b);
intmax_t		ft_clamp(intmax_t val, intmax_t min, intmax_t max);
intmax_t		ft_abs(intmax_t val);

#endif
