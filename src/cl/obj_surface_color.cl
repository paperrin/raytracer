#ifndef OBJ_SURFACE_COLOR_CL
# define OBJ_SURFACE_COLOR_CL

#include "shared.h"
#include "obj_surface_uv_map.cl"

float3		obj_surface_color(
		t_obj *obj,
		constant t_material *materials,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real3 point);
float3		texture_get_color(
		constant t_texture *texture,
		global uchar *texture_pixels,
		ulong n_texture_pixels,
		uint x, uint y);
float3		texture_uv_color(
		constant t_texture *textures,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real2 uv);

t_real2		transform_uv(t_real2 uv, t_real2 translate, t_real2 scale);

float3		obj_surface_color(
		t_obj *obj,
		constant t_material *materials,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real3 point)
{
	t_texture texture;

	if (materials[obj->material_id].texture_id == -1)
		return (materials[obj->material_id].color);
	else if ((uint)materials[obj->material_id].texture_id < textures_size)
	{
		texture = textures[materials[obj->material_id].texture_id];
		return (texture_uv_color(
					&textures[materials[obj->material_id].texture_id],
					texture_pixels,
					n_texture_pixels,
					obj_surface_uv_map(obj, point)));
	}
	return ((float3)(0.078, 1, 0.576));
}

float3		texture_get_color(constant t_texture *texture, global uchar *texture_pixels, ulong n_texture_pixels, uint x, uint y)
{
	uint3			color;
	ulong		offset;
	int				n_bytes;
	uchar3			c;		

	n_bytes = (texture->max_val <= 255) ? 1 : 2;
	x = x % texture->width;
	y = y % texture->height;
	offset = texture->pixels_offset + (y * texture->width + x) * n_bytes;
	if (offset >= n_texture_pixels)
		return ((float3)(1, 0.078, 0.576));
	
	c = (uchar3)(
		texture_pixels[offset * 3 + 0 * n_bytes],
		texture_pixels[offset * 3 + 1 * n_bytes],
		texture_pixels[offset * 3 + 2 * n_bytes]);
	color = convert_uint3(c);
	if (n_bytes == 2)
	{
		color.r <<= 8;
		color.g <<= 8;
		color.b <<= 8;
		offset += 1;
		c = (uchar3)(
			texture_pixels[offset * 3 + 0 * n_bytes],
			texture_pixels[offset * 3 + 1 * n_bytes],
			texture_pixels[offset * 3 + 2 * n_bytes]);
		color.r |= c.r;
		color.g |= c.g;
		color.b |= c.b;
	}
	return ((float3)((float)color.r / texture->max_val, (float)color.g / texture->max_val, (float)color.b / texture->max_val));
}

t_real2		transform_uv(t_real2 uv, t_real2 translate, t_real2 scale)
{
	uv /= scale;
	uv += translate;
	uv -= floor(uv);
	return (uv);
}

float3		texture_uv_color(
		constant t_texture *texture,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real2 uv)
{
	uint2	pos;
	float3	colors[4];
	float2	interp;

	uv = transform_uv(uv, texture->translate, texture->scale);
	uv = (t_real2)(uv.x * texture->width, uv.y * texture->height);
	pos = (uint2)(uv.x, uv.y);
	colors[0] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x, pos.y);
	if (texture->filter != e_filter_bilinear)
		return (colors[0]);
	colors[1] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x + 1, pos.y);
	colors[2] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x, pos.y + 1);
	colors[3] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x + 1, pos.y + 1);
	interp = (float2)(uv.x - pos.x, uv.y - pos.y);
	colors[1] = colors[0] * (1 - interp.x) + colors[1] * interp.x;
	colors[2] = colors[2] * (1 - interp.x) + colors[3] * interp.x;
	return (colors[1] * (1 - interp.y) + colors[2] * interp.y);
}

#endif
