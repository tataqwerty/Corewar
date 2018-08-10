/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:08:18 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:08:20 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				usage(void)
{
	ft_printf("{yellow}Usage:{eoc} ./corewar [-dump N -v | -v | -s IP | -c IP] "
	"[[-n N] <champion1.cor> <...cor>]\n"
	"   {red}-n{eoc}         : Number of player\n"
	"{blue}### {yellow}TEXT OUTPUT MODE{eoc} {blue}###"
	"#########################################################{eoc}\n"
	"   {red}-dump N{eoc}    : Dumps memory after N cycles then exits\n"
	"{blue}### {yellow}NCURSES OUTPUT MODE{eoc} {blue}###"
	"######################################################{eoc}\n"
	"   {red}-v{eoc}         : Ncurses output mode\n"
	"   {red}-dump N -v{eoc} : Dumps memory in Ncurses output mode after"
	" N cycles then exits\n"
	"{blue}### {yellow}NETWORK GAME MODE{eoc} {blue}###"
	"########################################################{eoc}\n"
	"   {red}-s IP{eoc}      : Start server on IP address\n"
	"                [./corewar -s 0.0.0.0]\n"
	"   {red}-c IP{eoc}      : Connect client to server which on IP address\n"
	"                [./corewar <champion.cor> -c 0.0.0.0]\n"
	"{blue}########################"
	"#########################################################{eoc}\n");
	exit(0);
}

void				ft_error(char *s)
{
	write(2, s, ft_strlen(s));
	exit(0);
}

unsigned int		reverse_bytes(unsigned int data, char bytes)
{
	unsigned int	res;

	res = data;
	if (bytes == 4)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[3];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[2];
		((unsigned char *)&res)[2] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[3] = ((unsigned char *)&data)[0];
	}
	else if (bytes == 2)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[0];
	}
	return (res);
}

/*
** This function gets a value of some sequence of bytes
** size of which specified in arg_size and returns reversed value.
*/

unsigned int		get_arg(unsigned int i, char arg_size)
{
	unsigned int	arg;
	unsigned char	str[4];
	unsigned char	j;

	j = 0;
	arg = 0;
	ft_bzero(str, 4);
	while (j < arg_size)
	{
		(i >= MEM_SIZE) ? (i = 0) : 0;
		str[j] = g_map[i];
		j++;
		i++;
	}
	((unsigned char *)&arg)[0] = ((unsigned char *)&str)[0];
	((unsigned char *)&arg)[1] = ((unsigned char *)&str)[1];
	((unsigned char *)&arg)[2] = ((unsigned char *)&str)[2];
	((unsigned char *)&arg)[3] = ((unsigned char *)&str)[3];
	return (reverse_bytes(arg, arg_size));
}

t_process			*push_new_process(t_process **head,
	unsigned int *process_count, t_bot *parent, unsigned int position)
{
	t_process	*new;

	new = (t_process *)malloc(sizeof(t_process));
	(!new) ? ft_error(ERR_101) : 0;
	ft_bzero(new->registries, REG_NUMBER + 1);
	new->registries[1] = parent->id;
	new->parent = parent;
	new->position = position;
	new->carry = 0;
	new->live = 0;
	new->opcode = 0;
	new->codage = 0;
	new->cycles_to_perform = 0;
	new->next = 0;
	if (*head)
		new->next = *head;
	*head = new;
	(*process_count)++;
	return (new);
}
