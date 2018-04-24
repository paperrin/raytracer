#ifndef ANTI_ALIASING_CL
# define ANTI_ALIASING_CL

#include "shared.h"

float4		get_pixel_xy(global float4 const *pixels, float2 uv, int2 size);
float4		get_pixel_offset(global float4 const *pixels, float2 uv, float2 offset, int2 size);
float4		get_pixel(uint x, uint y, global float4 const *pixels, int2 size);
float4		bilinear_interpolation(global float4 const *pixels, float2 uv, int2 size);
float4		anti_aliasing(global t_config const *const config, t_anti_aliasing *luma, global float4 const *pixels);
float		get_luma(float4 const pixel);
float		get_final_offset(t_anti_aliasing *luma, float lumaend1, float lumaend2, float dist1, float dist2);
float		sub_pixel_aa(t_anti_aliasing *luma);
void		find_edges(t_anti_aliasing *luma, float2 uv, global float4 const *pixels, int2 size);
void		get_edge_orientation(t_anti_aliasing *luma, global float4 const *pixels, int2 size);
float		get_interval(int i);

float		get_luma(float4 const pixel)
{
	return(sqrt(dot(pixel, float4(0.299f, 0.587f, 0.114f))));
}

float		get_interval(int i)
{
	if (i > 5)
	{
		if (i == 6)
			return((float)i * 1.5);
		if (i == 12)
			return((float)i * 8.0);
		if (i == 11)
			return((float)i * 4.0);
		if (i < 11)
			return((float)i * 2.0);
	}
	return (i);
}

void		get_edge_orientation(t_anti_aliasing *luma, global float4 const *pixels, int2 size)
{
	float	luma1 = luma->is_horizontal ? luma->orig.down : luma->orig.left;
	float	luma2 = luma->is_horizontal ? luma->orig.up : luma->orig.right;
	float	grad1 = luma1 - luma->center;
	float	grad2 = luma2 - luma->center;
	float2	inversesize = (float2)(1.f / size.x, 1.f / size.y);
	int		issteepest = fabs(grad1) >= fabs(grad2);

	luma->step_length = luma->is_horizontal ? inversesize.x : inversesize.y;
	luma->local_average = 0.0f;
	luma->gradscaled = 0.25f * fmax(fabs(grad1), fabs(grad2));
	if (issteepest)
	{
		luma->step_length = -luma->step_length;
		luma->local_average = 0.5f * (luma1 + luma->center);
	}
	else
		luma->local_average = 0.5f * (luma2 + luma->center);
}

float		get_final_offset(t_anti_aliasing *luma, float lumaend1, float lumaend2, float dist1, float dist2)
{
	float	distfinal = 0;
	float	edge_thick = dist1 + dist2;
	float	pixel_offset = 0;
	int		is_center_underavr = 0;
	int		correct_var = 0;
	int		is_directionx;

	distfinal = fmin(dist1, dist2);
	is_directionx = dist1 < dist2;
	pixel_offset = -distfinal / edge_thick + 0.5;
	is_center_underavr = luma->center < luma->local_average;
	correct_var = ((is_directionx ? lumaend1 : lumaend2) < 0.0);// != is_center_underavr;
	//return (correct_var == is_center_underavr ? pixel_offset : 0.0);
	return (pixel_offset);
}

void		find_edges(t_anti_aliasing *luma, float2 uv, global float4 const *pixels, int2 size)
{
	float2	currentuv = uv;
	float2	offset;
	float2	uv1;
	float2	uv2;
	float	lumaend1 = 0;
	float	lumaend2 = 0;
	int		reached1 = 0;
	int		reached2 = 0;
	int		reachedboth = 0;
	int		i = 2;

	if (luma->is_horizontal)
		currentuv.y += luma->step_length * 0.5;
	else
		currentuv.x += luma->step_length * 0.5;
	offset = luma->is_horizontal ? (float2)(1.f / (float)size.x, 0.0) : (float2)(0.0, 1.f / (float)size.y);
	uv1 = currentuv - offset;
	uv2 = currentuv + offset;
	lumaend1 = get_luma(get_pixel_xy(pixels, uv1, size));
	lumaend2 = get_luma(get_pixel_xy(pixels, uv2, size));
	lumaend1 -= luma->local_average;
	lumaend2 -= luma->local_average;
	reached1 = fabs(lumaend1) >= luma->gradscaled;
	reached2 = fabs(lumaend2) >= luma->gradscaled;
	reachedboth = reached1 && reached2;
	if (!reached1)
		uv1 -= offset;
	if (!reached2)
		uv2 += offset;
	if (!reachedboth)
	{
		while (i < 13)
		{
			if (!reached1)
				lumaend1 = get_luma(get_pixel_xy(pixels, uv1, size)) - luma->local_average;
			if (!reached2)
				lumaend2 = get_luma(get_pixel_xy(pixels, uv2, size)) - luma->local_average;
			reached1 = fabs(lumaend1) >= luma->gradscaled;
			reached2 = fabs(lumaend2) >= luma->gradscaled;
			reachedboth = reached1 && reached2;
			if (!reached1)
				uv1 -= offset * get_interval(i);
			if (!reached2)
				uv2 += offset * get_interval(i);
			if (reachedboth)
				break;
			i++;
		}
	}
	luma->final_offset = get_final_offset(luma, lumaend1, lumaend2,
			luma->is_horizontal ? (uv.x - uv1.x) : (uv.y - uv1.y),
			luma->is_horizontal ? (uv2.x - uv.x) : (uv2.y - uv.y));
}

float		sub_pixel_aa(t_anti_aliasing *luma)
{
	float	luma_average = (1.f / 12.f) * (2.f * (luma->x_axis + luma->y_axis) + luma->corners.left + luma->corners.right);
	float	sub_pixel_offset1 = clamp((float)(fabs(luma_average - luma->center) / luma->range), 0.f, 1.f);
	float	sub_pixel_offset2 = (-2.f * sub_pixel_offset1 + 3.f) * sub_pixel_offset1 * sub_pixel_offset1;
	float	sub_pixel_final_offset = sub_pixel_offset2 * sub_pixel_offset2 * 0.75f;

	return (fmax(luma->final_offset, sub_pixel_final_offset));
}

float4		anti_aliasing(global t_config const *const config, t_anti_aliasing *luma, global float4 const *pixels)
{
	const int	gid = get_global_id(0);
	int2		size = (int2)config->screen_size;
	float2		uv = (float2)(gid % size.x, (gid - (gid % size.x)) / size.x);
	float2		finaluv = uv;
	float		downleft;
	float		downright;
	float		upleft;
	float		upright;
	float		edge_x;
	float		edge_y;
	float4		lum;

	downleft = get_luma(get_pixel_offset(pixels, uv, (float2)(-1, -1), size));
	upright = get_luma(get_pixel_offset(pixels, uv, (float2)(1, 1), size));
	upleft = get_luma(get_pixel_offset(pixels, uv, (float2)(-1, 1), size));
	downright = get_luma(get_pixel_offset(pixels, uv, (float2)(1, -1), size));
	luma->x_axis = luma->orig.left + luma->orig.right;
	luma->y_axis = luma->orig.down + luma->orig.up;
	luma->corners.up = upleft + upright;
	luma->corners.down = downleft + downright;
	luma->corners.left = downleft + upleft;
	luma->corners.right = upright + downright;
	edge_x = fabs(-2.0 * luma->orig.left + luma->corners.left) + fabs(-2.0 * luma->center + luma->y_axis)
														* 2.0 + fabs(-2.0 * luma->orig.right + luma->corners.right);
	edge_y = fabs(-2.0 * luma->orig.up + luma->corners.up) + fabs(-2.0 * luma->center + luma->x_axis)
													* 2.0 + fabs(-2.0 * luma->orig.down + luma->corners.down);
	if (edge_x >= edge_y)
		luma->is_horizontal = 1;
	else
		luma->is_horizontal = 0;
	get_edge_orientation(luma, pixels, size);
	find_edges(luma, uv, pixels, size);
	luma->final_offset = sub_pixel_aa(luma);
/*	if (config->mouse_pxl_id == gid)
	{
		printf("%f * %f = %f\n", luma->final_offset, luma->step_length, luma->final_offset * luma->step_length);
		printf("center = %f, up = %f, down = %f, left = %f, right = %f\n", luma->center, luma->orig.down, luma->orig.up, luma->orig.left, luma->orig.right);
	//	printf("",);
		printf("downc = %f, leftc = %f, rightc = %f, upc = %f\n", luma->corners.down, luma->corners.left, luma->corners.right, luma->corners.up);
	}
*/	if (luma->is_horizontal)
		finaluv.y += luma->final_offset * luma->step_length;
	else
		finaluv.x += luma->final_offset * luma->step_length;
	if (fabs(luma->final_offset * luma->step_length) > 0.01)
		printf("%f\n", luma->final_offset * luma->step_length);
	lum.rgb = (float3)(luma->center);
	lum.a = 1;
	lum = lum * (1 + lum);
	float4 curr, final;
	curr = get_pixel_xy(pixels, uv, size);
	final = get_pixel_xy(pixels, finaluv, size);
	final -= curr;
	if (fabs(dot(final, (float4)(1))) / 4.f > 0.001)
	{
		printf("%v4f\n", final);
	}
	//return (get_pixel_xy(pixels, finaluv, size));
		return (lum);
}

float4		get_pixel_xy(global float4 const *pixels, float2 uv, int2 size)
{
	if (fmod(uv.x, 1.f) || fmod(uv.y, 1.f))
		return(bilinear_interpolation(pixels, uv, size));
	if (uv.x + (uv.y * (float)size.x) > (float)size.x * (float)size.y || uv.x + (uv.y * (float)size.x) < 0)
		return ((float4)(0, 0, 0, 0));
	return(get_pixel(uv.x, uv.y, pixels, size));
}

float4		get_pixel_offset(global float4 const *pixels, float2 uv, float2 offset, int2 size)
{
	if ((offset.x + uv.x) + ((uv.y - offset.y) * (float)size.x) > size.x * size.y)
		return (0);
	return (get_pixel(uv.x + offset.x, uv.y - offset.y, pixels, size));
}

float4		get_pixel(uint x, uint y, global float4 const *pixels, int2 size)
{
	if (x + (y * (uint)size.x) > (uint)size.x * (uint)size.y)
		return ((float4)(0, 0, 0, 0));
	return(pixels[x + (y * size.x)]);
}

float4		bilinear_interpolation(global float4 const *pixels, float2 uv, int2 size)
{
	float4	area[4];
	int2	area_rect[2];
	int2	pos;
	float2	interp;

	pos = (int2)(uv.x, uv.y);
	area_rect[0] = (int2)(pos.x, pos.y);
	area_rect[1] = (int2)(pos.x + (pos.x + 1 < size.x), pos.y + (pos.y + 1 < size.y));
	interp = (float2)(uv.x - (float)pos.x, uv.y - (float)pos.y);

	area[0] = get_pixel(area_rect[0].x, area_rect[0].y, pixels, size);
	area[1] = get_pixel(area_rect[1].x, area_rect[0].y, pixels, size);
	area[2] = get_pixel(area_rect[0].x, area_rect[1].y, pixels, size);
	area[3] = get_pixel(area_rect[1].x, area_rect[1].y, pixels, size);

	area[1] = area[1] * interp.x + area[0] * (1.f - interp.x);
	area[2] = area[3] * interp.x + area[2] * (1.f - interp.x);
	return (area[2] * interp.y + area[1] * (1.f - interp.y));
}

#endif
