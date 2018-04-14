#include "shared.h"

float4			to_sepia(global t_config const *const config, global float pixel);
float4			to_grayscale(global t_config const *const config, global float pixel);
float			get_luma(global float4 pixel);
float4			detect_aa(global t_config const *const config, global float *pixels);

float			get_luma(global float4 pixel)
{
	return(sqrt(dot(pixel, float3(0.299, 0.587, 0.114))));
}

float4			detect_aa(global t_config const *const config, global float4 *pixels)
{
	const int	gid = get_global_id(0);
	float		lcenter;
	float		ldown = 0;
	float		lright = 0;
	float		lup = 0;
	float		lleft = 0;
	float		lmin;
	float		lmax;
	float		lrange;

	lcenter = get_luma(pixels[gid]);
	if (gid > 1)
		lleft = get_luma(pixels[gid - 1]);
	if (gid < config->screen_size.x * config->screen_size.y)
		lright = get_luma(pixels[gid + 1]);
	if (gid > config->screen_size.x)
		lup = get_luma(pixels[gid - config->screen_size.x]);
	if (gid < (config->screen_size.x * config->screen_size.y) - config->screen_size.x)
		ldown = get_luma(pixels[gid + config->screen_size.x]);
	lmin = fmin(lcenter, fmin(fmin(ldown, lup), fmin(lleft, lright)));
	lmin = fmax(lcenter, fmax(fmax(ldown, lup), fmax(lleft, lright)));
	lrange = lmax - lmin;
	if (lrange < fmax(0.0312, lmax * 0.125))
		return (pixels[gid]);
	return(anti_aliasing(config, pixels));
}

float4			to_sepia(global t_config const *const config, global float pixel)
{
	const float3	tr = (float3)(0.393, 0.769, 0.189);
	const float3	tg = (float3)(0.349, 0.686, 0.168);
	const float3	tb = (float3)(0.272, 0.534, 0.131);
	float4		color;

	color = ((global float4)pixel);
	color.r = dot(color.rgb, tr);
	color.g = dot(color.rgb, tg);
	color.b = dot(color.rgb, tb);
	return (color);
}

float4			to_grayscale(global t_config const *const config, global float pixel)
{
	const		float3 trgb = (float3)(0.2126, 0.7152, 0.0722);
	float4		color;

	color = ((global float4)pixel);
	color.rgb = dot(color.rgb, trgb);
	return (color);
}

kernel void		kernel_post_process(
	global read_only t_config const *const config,
	global read_only float const *input,
	global write_only float *output)
{
	const		int gid = get_global_id(0);
	//placeholder
	if (config->post_filters == e_post_filter_sepia)
		((global float4*)pixels)[gid] = to_sepia(config, pixels[gid]);
	else if (config->post_filters == e_post_filter_grayscale)
		((global float4*)pixels)[gid] = to_grayscale(config, pixels[gid]);
}
