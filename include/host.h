/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:27:58 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/27 18:13:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOST_H
# define HOST_H

# include "t_real.h"
# include "shared.h"

typedef union	u_real2s
{
	t_real2		v;
	t_real		s[2];
}				t_real2s;

typedef union	u_real3s
{
	t_real3		v;
	t_real		s[3];
}				t_real3s;

#endif
