/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_bot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:54:31 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/16 12:54:35 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_bites(unsigned int num_value, char bytes)
{
	unsigned char *num;

	num = (unsigned char *)&num_value;
	if (bytes == 2)
		ft_printf("%-3d %-3d%11c", num[1], num[0], ' ');
	else if (bytes == 4)
		ft_printf("%-3d %-3d %-3d %-3d%3c", num[3], num[2], num[1], num[0],
		' ');
}

static void	write_str_or_num(char str, t_arg *arg)
{
	while (arg)
	{
		if (str == 1 && arg->str_value)
		{
			if (arg->type == 1)
				ft_printf("%%:%-16s", arg->str_value);
			else
				ft_printf(":%-17s", arg->str_value);
		}
		else if (str == 1)
		{
			if (arg->type == 0)
				ft_printf("r");
			else if (arg->type == 1)
				ft_printf("%%");
			ft_printf("%-17d", arg->num_value);
		}
		else if (str == 16 && arg->type != 0)
			write_bites((unsigned int)arg->num_value, arg->arg_size);
		else
			ft_printf("%-18d", arg->num_value);
		arg = arg->next;
	}
}

static void	write_header(t_asm *asmb)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", asmb->prog_size);
	ft_printf("Name : \"%s\"\n", asmb->prog_name);
	ft_printf("Comment : \"%s\"\n\n", asmb->comment);
}

static void	write_codage(t_command *command)
{
	ft_printf("\n%20c", ' ');
	if (command->codage)
		ft_printf("%-4d%-6d", command->opcode, command->codage);
	else
		ft_printf("%-10d", command->opcode);
}

void		show_bot(t_asm *asmb, t_command *command)
{
	write_header(asmb);
	while (command)
	{
		if (command->labels && command->labels->content)
		{
			while (command->labels)
			{
				ft_printf("%-11d:", command->bb);
				ft_printf("%4c%s:\n", ' ', command->labels->content);
				command->labels = command->labels->next;
			}
			if (!command->opcode)
				break ;
		}
		ft_printf("%-5d(%-3d) :", command->bb, command->bytes);
		ft_printf("%8c%-10s", ' ', command->name);
		write_str_or_num(1, command->args);
		write_codage(command);
		write_str_or_num(16, command->args);
		write_codage(command);
		write_str_or_num(0, command->args);
		ft_printf("\n\n");
		command = command->next;
	}
}
