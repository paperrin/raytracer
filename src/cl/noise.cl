#ifndef NOISE_CL
# define NOISE_CL

float		noise(int offset);
float		noise_2d(int x, int y);
float		cubic_interp(float before_p1, float p1, float p2, float after_p2, float t);
float		smooth_noise_2d(float x, float y);
float		smooth_noise_line(int x, int y, float frac_part_x);
int			get_int_part(float v);

float		noise(int offset)
{
	offset = (offset << 13) ^ offset;
	offset = (offset * (offset * offset * 15731 + 789221) + 1376312589);
	return ((1.f - (offset & 0x7fffffff) / 1073741824.f + 1.f) / 2.f);
}

float		noise_2d(int x, int y)
{
	int		n = noise(x) * 850000;
	return (noise(n + y));
}

float		cubic_interp(float before_p1, float p1, float p2, float after_p2, float t)
{
	float a = -0.5f * before_p1 + 1.5f * p1 - 1.5f * p2 + 0.5f * after_p2;
	float b = before_p1 - 2.5f * p1 + 2.f * p2 - 0.5f * after_p2;
	float c = -0.5f * before_p1 + 0.5f * p2;
	float d = p1;
	return (a * t * t * t + b * t * t + c * t + d);
}

int			get_int_part(float v)
{
	if (v >= 0)
		return ((int)v);
	else
		return ((int)v - 1);
}

float		smooth_noise_line(int x, int y, float frac_part_x)
{
	float		n[4];

	n[0] = noise_2d(x - 1, y);
	n[1] = noise_2d(x, y);
	n[2] = noise_2d(x + 1, y);
	n[3] = noise_2d(x + 2, y);
	return (cubic_interp(n[0], n[1], n[2], n[3], frac_part_x));
}

float		smooth_noise_2d(float x, float y)
{
	int2	int_part = (int2)(get_int_part(x), get_int_part(y));
	float2	frac_part = (float2)(x - (float)int_part.x, y - (float)int_part.y);
	float	n[4];

	n[0] = smooth_noise_line(int_part.x, int_part.y - 1, frac_part.x);
	n[1] = smooth_noise_line(int_part.x, int_part.y, frac_part.x);
	n[2] = smooth_noise_line(int_part.x, int_part.y + 1, frac_part.x);
	n[3] = smooth_noise_line(int_part.x, int_part.y + 2, frac_part.x);
	return (cubic_interp(n[0], n[1], n[2], n[3], frac_part.y));
}

#endif
