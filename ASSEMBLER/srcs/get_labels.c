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

static	void	get_label(t_list **labels, char *s, int *j)
{
	int			tmp;
	char		*tmp_s;

	tmp = *j;
	while (s[*j] && s[*j] != ':')
		(*j)++;
	tmp_s = my_strsub(s, tmp, *j);
	ft_list_pushback(labels, tmp_s);
	free(tmp_s);
	(*j)++;
}

void			get_labels(t_asm *asmb, t_command *new, int *j)
{
	char		*s;

	while (asmb->line)
	{
		comment_delete(asmb->line);
		s = asmb->line;
		skip_shit(s, j, " \t");
		if (str_has(s, LABEL))
			get_label(&new->labels, s, j);
		skip_shit(s, j, " \t");
		if (s[*j] != '\0')
			return ;
		*j = 0;
		ft_strdel(&asmb->line);
		get_next_line(asmb->fd, &asmb->line);
		if (asmb->line)
			asmb->last_line_size = ft_strlen(asmb->line);
	}
}
