/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:10:05 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/13 08:38:17 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		*ft_realloc(char *ptr, int size)
{
	int				i;
	char			*new_ptr;

	i = 0;
	if (!(new_ptr = ft_strnew(size)))
		return (0);
	if (ptr)
	{
		while (ptr[i] != '\0')
		{
			new_ptr[i] = ptr[i];
			i++;
		}
		free(ptr);
	}
	return (new_ptr);
}

static	int			ft_put_n(char *buffer, char **line, int *size)
{
	int				flag;
	int				n;

	n = 0;
	flag = 0;
	if (buffer[0] == '\0')
		return (0);
	while (buffer[n] != '\0' && buffer[n] != '\n')
		n++;
	(*size) += n;
	*line = ft_realloc(*line, *size);
	ft_memccpy(*line + ft_strlen(*line), buffer, '\n', n);
	if (buffer[n] == '\n')
	{
		flag = 1;
		n++;
		ft_memmove(buffer, buffer + n, ft_strlen(buffer) - n);
		ft_bzero(buffer + ft_strlen(buffer) - n, n);
	}
	else
		ft_bzero(buffer, n);
	return (flag);
}

int					get_next_line(const int fd, char **line)
{
	int				bytes;
	int				size;
	static	char	buffer[BUFF_SIZE];

	size = 0;
	if (!line || (read(fd, buffer, 0)) == -1)
		return (-1);
	*line = NULL;
	if (ft_put_n(buffer, line, &size) == 1)
		return (1);
	while ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		if (bytes != BUFF_SIZE)
			ft_bzero(buffer + bytes, BUFF_SIZE - bytes);
		if ((ft_put_n(buffer, line, &size)) == 1)
			return (1);
	}
	return (((*line) == NULL) ? 0 : 1);
}
