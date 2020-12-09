/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragog <maragog@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:36:06 by maragog           #+#    #+#             */
/*   Updated: 2020/08/06 10:16:50 by maragog          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char			*new_func(size_t size, char *res)
{
	char			*new;
	int				i;

	i = 0;
	if (!(new = malloc(size + 1)))
		return (0);
	while (res && res[i] != '\n' && res[i] != '\0')
	{
		new[i] = res[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char			*newstore_func(size_t size, char *res)
{
	char			*newstore;
	size_t			i;

	if (!(newstore = malloc(ft_strlen(res) - size)))
		return (0);
	i = 0;
	if (size++ != ft_strlen(res))
	{
		while (res[size] != '\0')
			newstore[i++] = res[size++];
		newstore[i] = '\0';
	}
	else
	{
		free(newstore);
		newstore = (0);
	}
	return (newstore);
}

static char			*from_store(char **s)
{
	char			*new;
	char			*newstore;
	char			*res;
	size_t			size;

	res = *s;
	size = 0;
	while (res && res[size] != '\n' && res[size] != '\0')
		size++;
	if (!(new = new_func(size, res)))
	{
		free(*s);
		return (0);
	}
	newstore = newstore_func(size, res);
	free(*s);
	*s = newstore;
	return (new);
}

static int			add_and_cut(char **to, char **from)
{
	char			*t_res;
	char			*f_res;
	size_t			i;
	char			*buff;

	t_res = *to;
	f_res = *from;
	i = 0;
	if (!(buff = malloc(ft_strlen(t_res) + ft_strlen(f_res) + 1)))
		return (0);
	while (t_res && *t_res != '\0')
		buff[i++] = *t_res++;
	while (f_res && *f_res != '\0')
		buff[i++] = *f_res++;
	buff[i] = '\0';
	free(*to);
	*to = buff;
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static char		*store[OPEN_MAX];
	char			*buff;
	int				bytes;
	char			*new;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX || !line)
		return (-1);
	buff = (0);
	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (!find_n(store[fd]) && (bytes = read(fd, buff, BUFFER_SIZE)))
	{
		if (bytes < 0)
			break ;
		buff[bytes] = '\0';
		add_and_cut(&store[fd], &buff);
	}
	free(buff);
	if (!(new = from_store(&store[fd])) || bytes < 0)
		return (-1);
	*line = new;
	if (!bytes && !store[fd])
		return (0);
	return (1);
}
