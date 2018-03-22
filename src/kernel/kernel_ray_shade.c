/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_shade.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:37:07 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/22 00:57:08 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_shade_create(t_app *app)
{
	cl_uint			mats_size;
	cl_uint			lights_size;
	cl_uint			textures_size;

	if (!opencl_kernel_create_n_args(&app->kernel_ray_shade, &app->ocl, 14))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_shade
				, "./src/cl/kernel_ray_shade.cl", "-I ./include/ -I ./src/cl/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_trace, 0))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 1);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_trace, 1))
		return (0);
	mats_size = ft_vector_size(&app->scene.v_material);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 2);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_material) * mats_size, (void*)app->scene.v_material.begin))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 3);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uint), (void*)&mats_size))
		return (0);
	lights_size = ft_vector_size(&app->scene.v_light);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 4);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_light) * lights_size, (void*)app->scene.v_light.begin))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 5);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uint), (void*)&lights_size))
		return (0);
	textures_size = ft_vector_size(&app->scene.v_texture);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 6);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_texture) * textures_size, (void*)app->scene.v_texture.begin))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 7);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uint), (void*)&textures_size))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 8);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uchar) * app->scene.n_texture_pixels * 3, (void*)app->scene.texture_pixels))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 9);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_ulong), (void*)&app->scene.n_texture_pixels))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 11);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_clear, 0))
		return (0);
	return (1);
}

int				kernel_ray_shade_launch(t_app *app)
{
	cl_int		err;

	if (app->n_rays == 0)
		return (1);
	app->kernel_ray_shade.work_size = app->n_rays;
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 10);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_ray_gen, 2))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 12);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_ray_gen, 0))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 13);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade,
			&app->kernel_ray_sort, 2))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_shade.kernel
		, 1, NULL, &app->kernel_ray_shade.work_size, NULL, 0, NULL, NULL)))
		return (error_cl_code(err));
	app->n_rays *= 2;
	return (1);
}

void		kernel_ray_shade_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_shade);
}
