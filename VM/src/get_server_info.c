/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_server_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:09:37 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:09:38 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_info_server(char *args[], int argv, int *i)
{
	g_vm->flag_server = 1;
	(*i)++;
	if (*i >= argv)
		usage();
	else
		g_vm->ip = args[*i];
	g_vm->flag_visual = 1;
}

void	get_info_client(char *args[], int argv, int *i)
{
	g_vm->flag_client = 1;
	(*i)++;
	if (*i >= argv)
		usage();
	else
		g_vm->ip = args[*i];
}
