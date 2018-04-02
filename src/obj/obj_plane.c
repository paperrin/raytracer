#include "rt.h"

t_obj			obj_plane(t_real3 pos, t_real3 normal, t_real3 up, t_mat_id material)
{
	t_obj		obj;

	obj.type = e_type_plane;
	obj.material_id = material;
	obj.as.plane.pos = pos;
	obj.as.plane.normal = normal;
	obj.as.plane.up = up;
	return (obj);
}
