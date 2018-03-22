/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:27:37 by ilarbi            #+#    #+#             */
/*   Updated: 2018/03/22 23:43:02 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ppm.h"


int		main(int argc, char **argv)
{
	size_t i;
	i = 0;
	//unsigned int max_val = 65535;
	//unsigned int max_val = 255;
	unsigned int max_val = 16037;
	t_fstream *fstream;
	float f[10] = {1., 0.5, 0., 0., 1., 1., 0.2, 0., 0., 1.};
	t_ppm_file file;

	if (argc != 2)
		return (1);	
	/*if ((file.fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU)) < 0)
	{
		ft_printf("Couldnt open file-> Error :");
		perror("");
		return (1);
	}
	close(file.fd);
	*/file.type = '6';
	file.width = 5;
	file.height = 2;
	file.max_val = max_val;
	file.color_depth_vector = ft_ppm_from_floats(&file, f);
/*	if (!ft_ppm_file_write(&file))
	{
		ft_printf("exits\n");
		close(file.fd);
		return (1);
	}*/
	i = 0;
	//char *read;
	fstream = ft_fstream_read_open(argv[1]);
	if (ft_ppm_read_header(fstream, &file.width, &file.height, &file.max_val))
			printf("OK\n");
   	/*if ((read = ft_ppm_get(argv[1], &file.width, &file.height, &file.max_val)))
	{
		ft_printf("get\n");
		while (i < file.width * file.height * size)
			ft_printf("%hhu ", read[i++]);
	}*/
	else
		printf("[main]invalid file \n");
	ft_fstream_close(&fstream);
	fstream = ft_fstream_read_open(argv[1]);
	if (ft_ppm_read_header(fstream, &file.width, &file.height, &file.max_val))
			printf("OK\n");
	else
		printf("[main]invalid file \n");
	ft_fstream_close(&fstream);
	//i = 0;
	//ft_printf("\nwrite\n");
	//while (i < file.width * file.height * size)
	//	ft_printf("%hhu ", file.color_depth_vector[i++]);
	
	ft_strdel((char **)&file.color_depth_vector);

	return (0);
}
