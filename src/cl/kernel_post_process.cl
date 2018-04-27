#include "shared.h"
#include "interpolation.cl"
#include "fxaa.cl"
#define EDGE_TRESHOLD_MIN 0.0312f
#define EDGE_TRESHOLD_MAX 0.0825f

float4			to_sepia(global t_config const *const config, float const pixel);
float4			to_grayscale(global t_config const *const config, float const pixel);
float4			detect_aa(global t_config const *const config, global float4 const *pixels);

float4			detect_aa(global t_config const *const config, global float4 const *pixels)
{
	uint			gid = get_global_id(0);
	int2		size = (int2)config->screen_size;
	float2		uv = (float2)(gid % size.x, (gid - (gid % size.x)) / size.x);
	t_anti_aliasing	luma;
	float			lmin = 0;
	float			lmax = 0;

	luma.center = get_luma(get_pixel_offset(pixels, uv, (float2)(0, 0), size));
	luma.orig.west = get_luma(get_pixel_offset(pixels, uv, (float2)(-1, 0), size));
	//if (uv.x != config->screen_size.x)
		luma.orig.east = get_luma(get_pixel_offset(pixels, uv, (float2)(1, 0), size));
	luma.orig.north = get_luma(get_pixel_offset(pixels, uv, (float2)(0, 1), size));
	//if (gid < (config->screen_size.x * config->screen_size.y) - config->screen_size.x - 2)
		luma.orig.south = get_luma(get_pixel_offset(pixels, uv, (float2)(0, -1), size));
	lmin = fmin(luma.center, fmin(fmin(luma.orig.south, luma.orig.north), fmin(luma.orig.west, luma.orig.east)));
	lmax = fmax(luma.center, fmax(fmax(luma.orig.south, luma.orig.north), fmax(luma.orig.west, luma.orig.east)));
	luma.range = lmax - lmin;
	if (luma.range < fmax(EDGE_TRESHOLD_MIN, lmax * EDGE_TRESHOLD_MAX))
		return (pixels[gid]);
	return (fast_approx_anti_aliasing(config, &luma, pixels));
}

float4			to_sepia(global t_config const *const config, float const pixel)
{
	const float3	tr = (float3)(0.393f, 0.769f, 0.189f);
	const float3	tg = (float3)(0.349f, 0.686f, 0.168f);
	const float3	tb = (float3)(0.272f, 0.534f, 0.131f);
	float4			color;

	color = ((float4)pixel);
	color.r = dot(color.rgb, tr);
	color.g = dot(color.rgb, tg);
	color.b = dot(color.rgb, tb);
	return (color);
}

float4			to_grayscale(global t_config const *const config, float const pixel)
{
	const		float3 trgb = (float3)(0.2126, 0.7152, 0.0722);
	float4		color;

	color = ((float4)pixel);
	color.rgb = dot(color.rgb, trgb);
	return (color);
}

kernel void		kernel_post_process(
	global read_only t_config const *const config,
	global read_only float const *input,
	global write_only float *output)
{
	//fxaa counter
	const		int gid = get_global_id(0);
	//placeholder
	if (config->post_filters == e_post_filter_sepia)
		((global float4*)output)[gid] = to_sepia(config, input[gid]);
	else if (config->post_filters == e_post_filter_grayscale)
		((global float4*)output)[gid] = to_grayscale(config, input[gid]);
	if (config->fxaa)
		((global float4*)output)[gid] = detect_aa(config, (global float4 const*)input);
}
