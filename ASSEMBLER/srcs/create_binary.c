/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:32:46 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/12 13:32:47 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			input_info(t_asm *asmb)
{
	char	null[4];

	ft_bzero(null, 4);
	write(asmb->new_fd, &asmb->magic, 4);
	write(asmb->new_fd, &asmb->prog_name, PROG_NAME_LENGTH);
	write(asmb->new_fd, &null, 4);
	write(asmb->new_fd, &asmb->prog_size, 4);
	write(asmb->new_fd, &asmb->comment, COMMENT_LENGTH);
	write(asmb->new_fd, &null, 4);
}

unsigned int		reverse_bytes(unsigned int x, char bytes)
{
	unsigned int	reversed;
	unsigned char	*n1;
	unsigned char	*n2;

	n1 = (unsigned char *)&x;
	n2 = (unsigned char *)&reversed;
	if (bytes == 2)
	{
		n2[0] = n1[1];
		n2[1] = n1[0];
	}
	else
	{
		n2[0] = n1[3];
		n2[1] = n1[2];
		n2[2] = n1[1];
		n2[3] = n1[0];
	}
	return ((bytes == 1) ? x : reversed);
}

static void			input_executable(t_command *command, t_arg *args, int fd)
{
	if (command->opcode)
		write(fd, &command->opcode, 1);
	if (command->codage)
		write(fd, &command->codage, 1);
	while (args)
	{
		args->num_value = reverse_bytes(args->num_value, args->arg_size);
		write(fd, &args->num_value, args->arg_size);
		args = args->next;
	}
}

static void			check_name(t_asm *asmb)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	while (asmb->file_name[i] != '\0')
	{
		if (asmb->file_name[i] == '.')
		{
			n = i;
			tmp = asmb->file_name;
			asmb->file_name = my_strsub(asmb->file_name, 0, n);
			free(tmp);
			tmp = asmb->file_name;
			asmb->file_name = ft_strjoin(asmb->file_name, ".cor");
			free(tmp);
			return ;
		}
		i++;
	}
	tmp = asmb->file_name;
	asmb->file_name = ft_strdup(".cor");
	free(tmp);
}

void				create_binary(t_asm *asmb, t_command *command)
{
	asmb->magic = reverse_bytes(asmb->magic, 4);
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);
	check_name(asmb);
	asmb->new_fd = open(asmb->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	input_info(asmb);
	while (command)
	{
		input_executable(command, command->args, asmb->new_fd);
		command = command->next;
	}
	ft_printf("Writing output program to %s\n", asmb->file_name);
	close(asmb->new_fd);
}
