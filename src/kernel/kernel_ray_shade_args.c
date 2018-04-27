/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_shade_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:48:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 13:54:59 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		add_texture_args(t_app *app)
{
	cl_uint			textures_size;
	cl_int			err;

	textures_size = ft_map_size(&app->scene.m_texture);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 6);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_texture) * textures_size
			, (void*)app->scene.m_texture.v_values.begin))
		return (0);
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_ray_shade.kernel
					, 7, sizeof(cl_uint), &textures_size)))
		return (error_cl_code(err));
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 8);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uchar) * app->scene.n_texture_pixels * 3
			, (void*)app->scene.texture_pixels))
		return (0);
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_ray_shade.kernel
					, 9, sizeof(cl_ulong), &app->scene.n_texture_pixels)))
		return (error_cl_code(err));
	return (1);
}

static int		add_material_and_light_args(t_app *app)
{
	cl_uint			mats_size;
	cl_uint			lights_size;
	cl_int			err;

	mats_size = ft_map_size(&app->scene.m_material);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 2);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_material) * mats_size
			, (void*)app->scene.m_material.v_values.begin))
		return (0);
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_ray_shade.kernel
					, 3, sizeof(cl_uint), &mats_size)))
		return (error_cl_code(err));
	lights_size = ft_map_size(&app->scene.m_light);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 4);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_light) * lights_size
			, (void*)app->scene.m_light.v_values.begin))
		return (0);
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_ray_shade.kernel
					, 5, sizeof(cl_uint), &lights_size)))
		return (error_cl_code(err));
	return (1);
}

static int		add_external_args(t_app *app)
{
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_trace, 0))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 1);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_trace, 1))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 10);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_ray_gen, 2))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 12);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_clear, 0))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 13);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_ray_gen, 0))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 14);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_ray_gen, 1))
		return (0);
	return (1);
}

int				kernel_ray_shade_args(t_app *app)
{
	if (!add_texture_args(app))
		return (0);
	if (!add_material_and_light_args(app))
		return (0);
	if (!add_external_args(app))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 11);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uint), (void*)&app->n_rays))
		return (0);
	return (1);
}
