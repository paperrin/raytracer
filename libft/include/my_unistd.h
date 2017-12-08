/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unistd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:52:11 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 16:57:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_UNISTD_H
# define MY_UNISTD_H

# ifdef _WIN32
#  include <io.h>
#  define STDIN_FILENO 0
#  define STDOUT_FILENO 1
#  define STDERR_FILENO 2
# else
#  include <unistd.h>
# endif

#endif
