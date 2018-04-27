#ifndef INTERPOLATION_CL
# define INTERPOLATION_CL

float4		get_pixel_xy(global float4 const *pixels, float2 uv, int2 size);
float4		get_pixel_offset(global float4 const *pixels, float2 uv, float2 offset, int2 size);
float4		get_pixel(uint x, uint y, global float4 const *pixels, int2 size);
float4		bilinear_interpolation(global float4 const *pixels, float2 uv, int2 size);

float4		get_pixel_xy(global float4 const *pixels, float2 uv, int2 size)
{
	float x_isdecimal = fmod(uv.x, 1.f);
	float y_isdecimal = fmod(uv.y, 1.f);

	if (x_isdecimal || y_isdecimal)
		return(bilinear_interpolation(pixels, uv, size));
	if (uv.x + (uv.y * (float)size.x) > (float)size.x * (float)size.y || uv.x + (uv.y * (float)size.x) < 0)
		return ((float4)(0, 0, 0, 0));
	return(get_pixel(uv.x, uv.y, pixels, size));
}

float4		get_pixel_offset(global float4 const *pixels, float2 uv, float2 offset, int2 size)
{
	if ((offset.x + uv.x) + ((uv.y + offset.y) * (float)size.x) > size.x * size.y)
		return (0);
	return (get_pixel(uv.x + offset.x, uv.y + offset.y, pixels, size));
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
