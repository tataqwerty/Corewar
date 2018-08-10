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

static	char	is_bot_name(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, NAME_CMD, ft_strlen(NAME_CMD)) == 0)
		return (1);
	return (0);
}

static	char	is_bot_comment(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, COMMENT_CMD, ft_strlen(COMMENT_CMD)) == 0)
		return (1);
	return (0);
}

/*
** This function copies string to dest after command and between brackets.
*/

static	void	copy_to_dst(t_asm *asmb, char *dest, int size, int *j)
{
	int			i;

	i = 0;
	while (asmb->line)
	{
		while (i < size && asmb->line[*j] && asmb->line[*j] != '\"')
			dest[i++] = asmb->line[(*j)++];
		if (asmb->line[*j] == '\"')
			return ;
		else if (i < size)
			dest[i++] = '\n';
		else
			ft_error((size == COMMENT_LENGTH) ? ERR_COMMENT_LEN : ERR_NAME_LEN);
		*j = 0;
		ft_strdel(&asmb->line);
		get_next_line(asmb->fd, &asmb->line);
	}
}

/*
** This function gets string after command.
*/

static	void	get_str(t_asm *asmb, char flag)
{
	int			j;
	int			size;
	char		*dest;

	j = ft_strstr(asmb->line, ((flag == GET_NAME) ? NAME_CMD : COMMENT_CMD)) -
		asmb->line + ft_strlen(((flag == GET_NAME) ? NAME_CMD : COMMENT_CMD));
	size = (flag == GET_NAME) ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	dest = (flag == GET_NAME) ? asmb->prog_name : asmb->comment;
	skip_shit(asmb->line, &j, " \t");
	(asmb->line[j] != '\"') ? ft_error(ERR_STRING) : j++;
	copy_to_dst(asmb, dest, size, &j);
	(!asmb->line || asmb->line[j] != '\"') ? ft_error(ERR_STRING) : j++;
	skip_shit(asmb->line, &j, " \t");
	if (asmb->line[j] != '\0' && asmb->line[j] != ';' && asmb->line[j] != '#')
		ft_error(ERR_STRING);
}

/*
** Function that gets prog_name and comment,
** and also checks if strings are valid or not.
** GET_NAME means that we are going to get name.
** GET_COMMENT means that we are going to get name.
*/

void			get_header(t_asm *asmb)
{
	char		flag;

	flag = 0;
	while (get_next_line(asmb->fd, &asmb->line) > 0)
	{
		if (is_bot_name(asmb->line))
		{
			(flag & 1) ? ft_error(ERR_SEVERAL_NAMES) : (flag = flag | 1);
			get_str(asmb, GET_NAME);
		}
		else if (is_bot_comment(asmb->line))
		{
			(flag & 2) ? ft_error(ERR_SEVERAL_COMMENTS) : (flag = flag | 2);
			get_str(asmb, GET_COMMENT);
		}
		else
		{
			comment_delete(asmb->line);
			(!check_line(asmb->line)) ? ft_error(ERR_STRING) : 0;
		}
		ft_strdel(&asmb->line);
		if (flag == 3)
			break ;
	}
	(flag != 3) ? ft_error(ERR_HEADER) : 0;
}
