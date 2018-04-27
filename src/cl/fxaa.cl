
#ifndef FXAA_CL
# define FXAA_CL
# define SUB_PIXEL_QUALITY 0.75f
# define FXAA_SEARCH_STEPS 12
# define FXAA_SEARCH_START 2

float4		fast_approx_anti_aliasing(global t_config const *const config, t_anti_aliasing *luma, global float4 const *pixels);
float		get_luma(float4 const pixel);
int			is_horizontal(global t_config const *const config, t_anti_aliasing *luma, float2 uv, global float4 const *pixels, int2 size);
float		get_local_average(global t_config const *const config, t_anti_aliasing *luma, global float4 const *pixels, int2 size);
void		find_edges(global t_config const *const config, t_anti_aliasing *luma, float2 uv, global float4 const *pixels, int2 size);
float		get_interval(int i);
float		get_final_offset(global t_config const *const config, t_anti_aliasing *luma, float lumaend1, float lumaend2, float dist1, float dist2);
float		sub_pixel_aa(t_anti_aliasing *luma);

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
		if (i >= 19)
			return((float)i * 16.0);
		if (i >= 12)
			return((float)i * 8.0);
		if (i == 11)
			return((float)i * 4.0);
		if (i < 11)
			return((float)i * 2.0);
	}
	return (i);
}

float4		fast_approx_anti_aliasing(global t_config const *const config, t_anti_aliasing *luma, global float4 const *pixels)
{
	const int	gid = get_global_id(0);
	int2		size = (int2)config->screen_size;
	float2		uv = (float2)(gid % size.x, (gid - (gid % size.x)) / size.x);
	float2		finaluv = uv;
	float		dist1;
	float		dist2;

	luma->is_horizontal = is_horizontal(config, luma, uv, pixels, size);
	luma->local_average = get_local_average(config, luma, pixels, size);
	find_edges(config, luma, uv, pixels, size);
	dist1 = luma->is_horizontal ? (uv.x - luma->end_one.uv.x) : (uv.y - luma->end_one.uv.y);
	dist2 = luma->is_horizontal ? (luma->end_two.uv.x - uv.x) : (luma->end_two.uv.y - uv.y);
	luma->final_offset = get_final_offset(config, luma, luma->end_one.luma, luma->end_two.luma, dist1, dist2);
	if (luma->is_horizontal)
		finaluv.y += luma->final_offset * luma->step_length;
	else
		finaluv.x += luma->final_offset * luma->step_length;
	float4		lum;
	lum.rgb = (float3)(luma->center);
	lum.a = 1;
	lum = lum * (1 + lum);
	if (config->mouse_pxl_id == gid)
	{
		printf("////////\ncenter = %f:%f at %f\n",uv.x, uv.y, luma->center);
		printf("north = %f:%f at %f, south = %f:%f at %f\n", uv.x, uv.y + 1, luma->orig.north, uv.x, uv.y - 1, luma->orig.south);
		printf("west = %f:%f at %f, east = %f:%f at %f\n", uv.x - 1, uv.y, luma->orig.west, uv.x + 1, uv.y, luma->orig.east);
		printf("end1 = %f:%f (%f) at %f\nend2 = %f:%f (%f) at %f\n",luma->end_one.uv.x, luma->end_one.uv.y, dist1, luma->end_one.luma,
				luma->end_two.uv.x, luma->end_two.uv.y, dist2, luma->end_two.luma);
		printf("-%f / %f + 0.5 = %f\n", fmin(dist1, dist2), dist1 + dist2, luma->final_offset);
		printf("is horizontal ? %d gradscale = %f avg = %f\n////////", luma->is_horizontal, luma->gradscaled, luma->local_average);
	}
	luma->final_offset = sub_pixel_aa(luma);
	//return (lum);
	return (get_pixel_xy(pixels, finaluv, size));
}

int		is_horizontal(global t_config const *const config, t_anti_aliasing *luma, float2 uv, global float4 const *pixels, int2 size)
{
	float		luma_sw;
	float		luma_se;
	float		luma_nw;
	float		luma_ne;
	float		edge_u;
	float		edge_v;

	luma_sw = get_luma(get_pixel_offset(pixels, uv, (float2)(-1, -1), size));
	luma_ne = get_luma(get_pixel_offset(pixels, uv, (float2)(1, 1), size));
	luma_nw = get_luma(get_pixel_offset(pixels, uv, (float2)(-1, 1), size));
	luma_se = get_luma(get_pixel_offset(pixels, uv, (float2)(1, -1), size));
	luma->x_axis = luma->orig.west + luma->orig.east;
	luma->y_axis = luma->orig.south + luma->orig.north;
	luma->corners.north = luma_nw + luma_ne;
	luma->corners.south = luma_sw + luma_se;
	luma->corners.west = luma_sw + luma_nw;
	luma->corners.east = luma_ne + luma_se;
	edge_u = fabs(-2.0 * luma->orig.west + luma->corners.west) + fabs(-2.0 * luma->center + luma->y_axis)
														* 2.0 + fabs(-2.0 * luma->orig.east + luma->corners.east);
	edge_v = fabs(-2.0 * luma->orig.north + luma->corners.north) + fabs(-2.0 * luma->center + luma->x_axis)
													* 2.0 + fabs(-2.0 * luma->orig.south + luma->corners.south);
	if (edge_u >= edge_v)
		return (1);
	return (0);
}

float		get_local_average(global t_config const *const config, t_anti_aliasing *luma, global float4 const *pixels, int2 size)
{
	float	luma1 = luma->is_horizontal ? luma->orig.south : luma->orig.west;
	float	luma2 = luma->is_horizontal ? luma->orig.north : luma->orig.east;
	float	gradient1 = luma1 - luma->center;
	float	gradient2 = luma2 - luma->center;

	luma->step_length = luma->is_horizontal ? 1.f : 1.f;
	luma->gradscaled = 0.25f * fmax(fabs(gradient1), fabs(gradient2));
	if (fabs(gradient1) >= fabs(gradient2))
	{
		luma->step_length = -luma->step_length;
		return (0.5f * (luma1 + luma->center));
	}
	else
		return (0.5f * (luma2 + luma->center));
}

void		find_edges(global t_config const *const config, t_anti_aliasing *luma, float2 uv, global float4 const *pixels, int2 size)
{
	float2	currentuv = uv;
	float2	offset;
	int		reached1 = 0;
	int		reached2 = 0;
	int		reachedboth = 0;
	int		i = FXAA_SEARCH_START;

	if (luma->is_horizontal)
		currentuv.y += luma->step_length * 0.5f;
	else
		currentuv.x += luma->step_length * 0.5f;
	offset = luma->is_horizontal ? (float2)(1.f, 0.0) : (float2)(0.0, 1.f);
	luma->end_one.uv = currentuv - offset;
	luma->end_two.uv = currentuv + offset;
	luma->end_one.luma = get_luma(get_pixel_xy(pixels, luma->end_one.uv, size)) - luma->local_average;
	luma->end_two.luma = get_luma(get_pixel_xy(pixels, luma->end_two.uv, size)) - luma->local_average;
	reached1 = fabs(luma->end_one.luma) >= luma->gradscaled;
	reached2 = fabs(luma->end_two.luma) >= luma->gradscaled;
	reachedboth = reached1 && reached2;
	if (config->mouse_pxl_id == get_global_id(0))
		printf("\n####one = %f:%f %f || two = %f:%f %f## rb: %d\n", luma->end_one.uv.x, luma->end_one.uv.y, luma->end_one.luma,
				luma->end_two.uv.x, luma->end_two.uv.y, luma->end_two.luma, reachedboth);
	if (!reached1)
		luma->end_one.uv -= offset;
	if (!reached2)
		luma->end_two.uv += offset;
	if (!reachedboth)
	{
		while (i < FXAA_SEARCH_STEPS && !reachedboth)
		{
			if (!reached1)
				luma->end_one.luma = get_luma(get_pixel_xy(pixels, luma->end_one.uv, size)) - luma->local_average;
			if (!reached2)
				luma->end_two.luma = get_luma(get_pixel_xy(pixels, luma->end_two.uv, size)) - luma->local_average;
			if (config->mouse_pxl_id == get_global_id(0))
			{
				printf("\n****one = %f:%f %f || two = %f:%f %f****off%f\n", luma->end_one.uv.x, luma->end_one.uv.y, luma->end_one.luma,
				luma->end_two.uv.x, luma->end_two.uv.y, luma->end_two.luma, offset.x * get_interval(i));
				if (i == FXAA_SEARCH_STEPS)
					printf("\nSTOP\n");
			}
			reached1 = fabs(luma->end_one.luma) >= luma->gradscaled;
			reached2 = fabs(luma->end_two.luma) >= luma->gradscaled;
			reachedboth = reached1 && reached2;
			if (!reached1)
				luma->end_one.uv -= offset * get_interval(i);
			if (!reached2)
				luma->end_two.uv += offset * get_interval(i);
			i++;
		}
	}
}

float		get_final_offset(global t_config const *const config, t_anti_aliasing *luma, float lumaend1, float lumaend2, float dist1, float dist2)
{
	float	distfinal = 0;
	float	edge_thick = dist1 + dist2;
	float	pixel_offset = 0;
	float	lumaend;
	int		is_center_underavr = 0;
	int		correct_var = 0;
	int		is_directionx;

	distfinal = fmin(dist1, dist2);
	is_directionx = dist1 < dist2;
	pixel_offset = -distfinal / edge_thick + 0.5;
	is_center_underavr = luma->center < luma->local_average;
	if (dist1 < dist2)
		lumaend = lumaend1;
	else
		lumaend = lumaend2;
	if ((lumaend < 0.0) != is_center_underavr)
		correct_var = 1;
	else
		correct_var = 0;
//	correct_var = ((is_directionx ? lumaend1 : lumaend2) < 0.0) != is_center_underavr;
	return (correct_var == is_center_underavr ? pixel_offset : 0.0);
}

float		sub_pixel_aa(t_anti_aliasing *luma)
{
	float	luma_average = (1.f / 12.f) * (2.f * (luma->x_axis + luma->y_axis) + luma->corners.west + luma->corners.east);
	float	sub_pixel_offset1 = clamp((float)(fabs(luma_average - luma->center) / luma->range), 0.f, 1.f);
	float	sub_pixel_offset2 = (-2.f * sub_pixel_offset1 + 3.f) * sub_pixel_offset1 * sub_pixel_offset1;
	float	sub_pixel_final_offset = sub_pixel_offset2 * sub_pixel_offset2 * SUB_PIXEL_QUALITY;

	return (fmax(luma->final_offset, sub_pixel_final_offset));
}

#endif
