#ifndef OBJ_SURFACE_COLOR_CL
# define OBJ_SURFACE_COLOR_CL

#include "shared.h"
#include "obj_surface_uv_map.cl"

cl_float3		obj_surface_color(
		t_obj *obj,
		constant t_material *materials,
		constant t_texture *textures, cl_uint textures_size,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		t_real3 point);
cl_float3		texture_uv_color(
		constant t_texture *textures,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		t_real2 uv);

cl_float3		obj_surface_color(
		t_obj *obj,
		constant t_material *materials,
		constant t_texture *textures, cl_uint textures_size,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		t_real3 point)
{
	if (materials[obj->material_id].texture_id == -1)
		return (materials[obj->material_id].color);
	else if ((cl_uint)materials[obj->material_id].texture_id < textures_size)
	{
		return (texture_uv_color(
					&textures[materials[obj->material_id].texture_id],
					texture_pixels,
					n_texture_pixels,
					obj_surface_uv_map(obj, point)));
	}
	return ((cl_float3)(0.078, 1, 0.576));
}

cl_float3		texture_uv_color(
		constant t_texture *texture,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		t_real2 uv)
{
	cl_uint2	pos;
	cl_ulong	pixel_offset;
	cl_float3	color;
	cl_uchar3	color_char;

	pos = (cl_uint2)(uv.x * texture->width, uv.y * texture->height);
	pos.x = clamp(pos.x, (uint)0, (uint)texture->width - 1);
	pos.y = clamp(pos.y, (uint)0, (uint)texture->height - 1);
	pixel_offset = pos.y * texture->width + pos.x;
	pixel_offset += texture->pixels_offset;
	if (pixel_offset >= n_texture_pixels)
		return ((cl_float3)(1, 0.078, 0.576));
	color_char.r = texture_pixels[pixel_offset * 3 + 0];
	color_char.g = texture_pixels[pixel_offset * 3 + 1];
	color_char.b = texture_pixels[pixel_offset * 3 + 2];
	color = (cl_float3)(color_char.r / 255.f, color_char.g / 255.f, color_char.b / 255.f);
	return (color);
}

#endif
