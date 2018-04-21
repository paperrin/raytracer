/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:42:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 17:19:02 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS_TYPE_H
# define CLASS_TYPE_H

typedef enum			e_class_type
{
	e_class_type_none,
	e_class_type_console,
	e_class_type_config,
	e_class_type_obj_sphere,
	e_class_type_obj_plane,
	e_class_type_obj_cylinder,
	e_class_type_obj_cone,
	e_class_type_obj_aligned_cube,
	e_class_type_point_light,
	e_class_type_distant_light,
	e_class_type_spot_light,
	e_class_type_camera,
	e_class_type_material,
	e_class_type_texture
}						t_e_class_type;

#endif
