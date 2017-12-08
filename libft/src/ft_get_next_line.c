/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:48:35 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 18:19:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static t_list		*cmp_f(t_list *elem, void *fd)
{
	if (((t_fd*)elem->content)->fd == *((int*)fd))
		return (elem);
	return (NULL);
}

static t_fd			*new_fd_container(int fd)
{
	t_fd	*container;

	container = (t_fd*)malloc(sizeof(t_fd));
	if (!container)
		return (NULL);
	container->fd = fd;
	container->buff = (char*)malloc(sizeof(char) * (1));
	if (!container->buff)
	{
		free(container);
		return (NULL);
	}
	container->buff[0] = '\0';
	container->read_pos = container->buff;
	container->nb_bytes = 0;
	return (container);
}

static int			update_buffer(t_fd *cur_s)
{
	int		bytes_read;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	cur_s->nb_bytes = ft_strlen(cur_s->read_pos);
	ft_bzero(buff, BUFF_SIZE + 1);
	if (!(tmp = ft_strdup(cur_s->read_pos)))
		return (-1);
	free(cur_s->buff);
	cur_s->buff = tmp;
	while (!ft_strchr(buff, '\n'))
	{
		if ((bytes_read = read(cur_s->fd, buff, BUFF_SIZE)) <= 0)
			return (bytes_read);
		if (!(tmp = ft_strjoin(cur_s->buff, buff)))
			return (-1);
		cur_s->nb_bytes += bytes_read;
		free(cur_s->buff);
		cur_s->buff = tmp;
	}
	cur_s->read_pos = cur_s->buff;
	return (cur_s->nb_bytes);
}

static int			read_fd(t_list **lst_fd, t_list *cur, char **line)
{
	int		bytes_read;
	t_fd	*cur_s;

	cur_s = ((t_fd*)cur->content);
	bytes_read = 1;
	if (cur_s->read_pos == cur_s->buff + cur_s->nb_bytes
			|| !ft_strchr(cur_s->read_pos, '\n'))
	{
		if ((bytes_read = update_buffer(cur_s)) <= 0)
			*lst_fd = ft_lstdelfind(*lst_fd, NULL, (void*)&cur_s->fd, &cmp_f);
	}
	if (bytes_read > 0)
		*line = cur_s->read_pos;
	return (bytes_read);
}

int					ft_get_next_line(const int fd, char **line)
{
	static t_list	*lst_fd;
	t_list			*cur;
	t_fd			*cur_s;
	char			*newl_pos;
	int				bytes_read;

	*line = NULL;
	cur = ft_lstfind(lst_fd, (void*)&fd, &cmp_f);
	if (!cur)
		ft_lstadd(&lst_fd, cur = ft_lstnew(new_fd_container(fd), sizeof(t_fd)));
	if (!cur || !cur->content)
		return (-1);
	cur_s = ((t_fd*)cur->content);
	if ((bytes_read = read_fd(&lst_fd, cur, line)) <= 0)
		return (bytes_read);
	if ((newl_pos = ft_strchr(cur_s->read_pos, '\n')))
	{
		cur_s->read_pos = newl_pos;
		*cur_s->read_pos++ = '\0';
	}
	else
		cur_s->read_pos = ft_strchr(cur_s->read_pos, '\0');
	return (1);
}
