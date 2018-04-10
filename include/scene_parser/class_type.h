/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:42:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 22:56:51 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS_TYPE_H
# define CLASS_TYPE_H

typedef enum			e_class_type
{
	e_class_type_none,
	e_class_type_console,
	e_class_type_obj_sphere,
	e_class_type_obj_plane,
	e_class_type_obj_cylinder,
	e_class_type_obj_cone,
	e_class_type_obj_cube,
	e_class_type_light_point,
	e_class_type_light_dir,
	e_class_type_light_spot,
	e_class_type_camera,
	e_class_type_material,
	e_class_type_texture
}						t_e_class_type;

#endif
