#include "rt.h"

t_obj			obj_cylinder(t_real3 pos, t_real3 normal, t_real3 up
		, t_real radius, t_mat_id material)
{
	t_obj		obj;

	obj.type = type_cylinder;
	obj.material_id = material;
	obj.as.cylinder.pos = pos;
	obj.as.cylinder.up = up;
	obj.as.cylinder.normal = normal;
	obj.as.cylinder.radius = radius;
	return (obj);
}
