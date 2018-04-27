#include "host.h"

void			to_sepia(global t_config const *const config, global float *pixels);
void			to_grayscale(global t_config const *const config, global float *pixels);

void			to_sepia(global t_config const *const config, global float *pixels)
{
	const		int gid = get_global_id(0);
	const		float3 tr = (float3)(0.393, 0.769, 0.189);
	const		float3 tg = (float3)(0.349, 0.686, 0.168);
	const		float3 tb = (float3)(0.272, 0.534, 0.131);
	float4		color;

	color = ((global float4*)pixels)[gid];
	color.r = dot(color.rgb, tr);
	color.g = dot(color.rgb, tg);
	color.b = dot(color.rgb, tb);
	((global float4*)pixels)[gid] = color;
}

void			to_grayscale(global t_config const *const config, global float *pixels)
{
	const		int gid = get_global_id(0);
	const		float3 trgb = (float3)(0.21, 0.72, 0.07);
	float4		color;

	color = ((global float4*)pixels)[gid];
	color.rgb = dot(color.rgb, trgb);
	((global float4*)pixels)[gid] = color;
}

kernel void		kernel_post_process(
	global write_only float *pixels,
	global read_only t_config const *const config)
{
	//placeholder
	if (config->post_filters == e_post_filter_sepia)
		to_sepia(config, pixels);
	else if (config->post_filters == e_post_filter_grayscale)
		to_grayscale(config, pixels);
}
