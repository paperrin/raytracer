#ifndef OBJ_SURFACE_COLOR_CL
# define OBJ_SURFACE_COLOR_CL

#include "host.h"
#include "obj_surface_uv_map.cl"
#include "noise.cl"

float3		obj_surface_color(
		t_obj *obj,
		constant t_material *materials,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real3 point);

float		obj_surface_refraction(
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

float3		texture_image_uv_color(
		constant t_texture *textures,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real2 uv);

t_real2		transform_uv(t_real2 uv, t_real2 translate, t_real2 scale);

float3		texture_checkerboard_uv_color(
			t_texture *texture, t_real2 uv);

float3		texture_default(t_real2 uv);

float3		texture_sine_uv_color(t_texture *texture, t_real2 uv);

float3		texture_noise_uv_color(
			t_texture *texture, t_real2 uv);

float		obj_surface_refraction(
		t_obj *obj,
		constant t_material *materials,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real3 point)
{
	t_texture		texture;
	t_mat_id		mat_id;
	cl_int			tex_id;
	float3			color;
	float			refraction;

	mat_id = obj->material_id;
	tex_id = materials[mat_id].refraction_map_id;
	refraction = materials[mat_id].refraction;
	if (tex_id > -1 && (uint)tex_id < textures_size)
	{
		texture = textures[tex_id];
		if (texture.type == e_texture_type_image)
		{
			color = texture_image_uv_color(
				&textures[tex_id], texture_pixels, n_texture_pixels,
				obj_surface_uv_map(obj, point));
		}
		else if (texture.type == e_texture_type_checkerboard)
			color = texture_checkerboard_uv_color(&texture, obj_surface_uv_map(obj, point));
		else if (texture.type == e_texture_type_sine)
			color = texture_sine_uv_color(&texture, obj_surface_uv_map(obj, point));
		refraction = clamp(color.b, 0.f, 1.f);
	}
	return (refraction);
}

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
		if (texture.type == e_texture_type_image)
		{
			return (texture_image_uv_color(
					&textures[materials[obj->material_id].texture_id],
					texture_pixels,
					n_texture_pixels,
					obj_surface_uv_map(obj, point)));
		}
		else if (texture.type == e_texture_type_checkerboard)
			return (texture_checkerboard_uv_color(&texture, obj_surface_uv_map(obj, point)));
		else if (texture.type == e_texture_type_sine)
			return (texture_sine_uv_color(&texture, obj_surface_uv_map(obj, point)));
		else if (texture.type == e_texture_type_noise)
			return (texture_noise_uv_color(&texture, obj_surface_uv_map(obj, point)));
	}
	return (texture_default(obj_surface_uv_map(obj, point)));
}

float3	texture_default(t_real2 uv)
{
	t_texture text;

	text.scale = (t_real2)(0.25);
	text.translate = (t_real2)(0);
	text.as.checkerboard.color1 = (t_real3)(1, 1, 1);
	text.as.checkerboard.color2 = (t_real3)(1, 0, 0.70);
	return (texture_checkerboard_uv_color(&text, uv));
}

float3		texture_get_color(constant t_texture *texture, global uchar *texture_pixels, ulong n_texture_pixels, uint x, uint y)
{
	uint3			color;
	ulong			offset;
	int				n_bytes;
	uchar3			c;

	n_bytes = (texture->as.image.max_val <= 255) ? 1 : 2;
	x = x % texture->as.image.width;
	y = y % texture->as.image.height;
	offset = texture->as.image.pixels_offset + (y * texture->as.image.width + x) * n_bytes;
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
	return ((float3)((float)color.r / texture->as.image.max_val, (float)color.g / texture->as.image.max_val, (float)color.b / texture->as.image.max_val));
}

t_real2		transform_uv(t_real2 uv, t_real2 translate, t_real2 scale)
{
	uv /= scale;
	uv += translate;
	return (uv);
}

float3		texture_image_uv_color(
		constant t_texture *texture,
		global uchar *texture_pixels, ulong n_texture_pixels,
		t_real2 uv)
{
	uint2	pos;
	float3	colors[4];
	float2	interp;

	uv = transform_uv(uv, texture->translate, texture->scale);
	uv -= floor(uv);
	uv = (t_real2)(uv.x * texture->as.image.width, uv.y * texture->as.image.height);
	pos = (uint2)(uv.x, uv.y);
	colors[0] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x, pos.y);
	if (texture->as.image.filter != e_filter_bilinear)
		return (colors[0]);
	colors[1] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x + 1, pos.y);
	colors[2] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x, pos.y + 1);
	colors[3] = texture_get_color(texture, texture_pixels, n_texture_pixels, pos.x + 1, pos.y + 1);
	interp = (float2)(uv.x - pos.x, uv.y - pos.y);
	colors[1] = colors[0] * (1 - interp.x) + colors[1] * interp.x;
	colors[2] = colors[2] * (1 - interp.x) + colors[3] * interp.x;
	return (colors[1] * (1 - interp.y) + colors[2] * interp.y);
}

float3		texture_checkerboard_uv_color(
			t_texture *texture, t_real2 uv)
{
	uv -= floor(uv);
	uv = transform_uv(uv, texture->translate, texture->scale);
	if  (((int)(uv.x * 2) + (int)(uv.y * 2)) % 2 == 0)
		return(texture->as.checkerboard.color1);
	else
		return (texture->as.checkerboard.color2);
}

float3		texture_noise_uv_color(
			t_texture *texture, t_real2 uv)
{
	float		noise;

	uv = transform_uv(uv, texture->translate, texture->scale);
	noise = smooth_noise_2d(uv.x, uv.y);
	return (texture->as.noise.color1 * noise
			+ texture->as.noise.color2 * (1.f - noise));
}

float3		texture_sine_uv_color(t_texture *texture, t_real2 uv)
{
	t_real2	sine;
	float3	colorx;
	float3	colory;

	uv -= floor(uv);
	uv = transform_uv(uv, texture->translate, texture->scale);
	sine.x = sin(uv.x * 2 * M_PI_F);
	sine.y = sin(uv.y * 2 * M_PI_F);
	sine = (sine + 1.f) / 2;
	colorx = texture->as.sine.color1 * sine.x + texture->as.sine.color2 * (1 - sine.x);
	colory = texture->as.sine.color3 * sine.y + texture->as.sine.color4 * (1 - sine.y);
	return (colorx * texture->as.sine.factors.x + colory * texture->as.sine.factors.y);
}

#endif
