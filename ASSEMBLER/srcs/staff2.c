/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 16:39:55 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/16 16:39:57 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		check_last_line(t_asm *asmb)
{
	char	s[asmb->last_line_size + 1];
	int		i;

	i = 0;
	ft_bzero(s, asmb->last_line_size + 1);
	lseek(asmb->fd, -asmb->last_line_size, SEEK_CUR);
	read(asmb->fd, &s, asmb->last_line_size);
	if (!str_has(s, LABEL) && !str_has(s, COMMAND))
		return (1);
	else
	{
		i = ft_strlen(s) - 1;
		if (s[i] == '\n')
			return (1);
	}
	return (0);
}

char		str_has(char *str, char flag)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (flag == LABEL)
	{
		while (str[i] && str[i] != ':')
			if (!ft_strchr(LABEL_CHARS, str[i++]))
				return (0);
		return ((i > 0 && str[i] == ':') ? 1 : 0);
	}
	else if (flag == COMMAND)
	{
		(str_has(str, LABEL)) ? (str = ft_strchr(str, ':') + 1) : 0;
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		while (str[i] && ft_isalpha(str[i]))
			i++;
		return ((i > 0 && index_of(str, i) != -1) ? 1 : 0);
	}
	return (0);
}

char		*my_strsub(char *src, int start, int end)
{
	char	*s;
	int		i;
	int		size;

	size = end - start;
	if (!(s = (char *)malloc(size + 1)))
		ft_error(ERR_MALLOC);
	ft_bzero(s, size + 1);
	i = 0;
	while (i < size)
	{
		s[i] = src[start + i];
		i++;
	}
	return (s);
}

void		check_argvs(t_asm *asmb, char **av, int ac)
{
	while (--ac > 0)
	{
		if (ft_strequ(av[ac], "-a"))
			asmb->flag_a = 1;
		else if (ft_strequ(av[ac], "-b"))
			asmb->flag_b = 1;
		else if (!asmb->file_name)
			asmb->file_name = ft_strdup(av[ac]);
	}
}

void		norm_file_name(char **file_name)
{
	char	*tmp;

	if (*file_name)
	{
		if (ft_strrchr(*file_name, '/'))
		{
			tmp = ft_strdup(ft_strrchr(*file_name, '/') + 1);
			ft_strdel(file_name);
			*file_name = tmp;
		}
	}
}
