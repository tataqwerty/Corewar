/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:45:19 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/11 13:45:23 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/libft.h"
# include <fcntl.h>

# define T_REG_SIZE				1
# define T_DIR_SIZE				2
# define T_IND_SIZE				2

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD				".name"
# define COMMENT_CMD			".comment"

# define REG_NUMBER				16

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define GET_NAME				1
# define GET_COMMENT			2
# define LABEL					1
# define COMMAND				2

# define UNDEFINED_TYPE			-1
# define T_REG					0
# define T_DIR					1
# define T_IND					2

# define STRING_VAL				1
# define UINT_VAL				2

/*
** ERRORS
*/

# define ERR_MALLOC "Error: memory was not allocated"
# define ERR_NOT_ENOUGH_DATA "Error: not enough data"
# define ERR_SEVERAL_NAMES "Error: file has several names"
# define ERR_SEVERAL_COMMENTS "Error: file has several comments"
# define ERR_STRING "Error: wrong string"
# define ERR_HEADER "Error: wrong header"
# define ERR_NAME_LEN "Error: too long name"
# define ERR_COMMENT_LEN "Error: too long comment"
# define ERR_COMMAND_NAME "Error: undefined command"
# define ERR_EOF "Error: invalid end of file"
# define ERR_UNDEFINED_ARG "Error: undefined argument"
# define ERR_NOT_COMPATIBLE_ARG "Error: not compatible argument"
# define ERR_TOO_MUCH_ARGS "Error: too much arguments"
# define ERR_TOO_MUCH_SEPARATORS "Error: too much comas"
# define ERR_COUNT_ARGS "Error: invalid quantity of arguments"
# define ERR_NEW_FILE "Error: invalid output file"
# define ERR_NO_SUCH_LABEL "Error: no such label"
# define ERR_FLAGS "Error: too much flags"

/*
** TO THE TABLE WE CAN REFER JUST WITH OPCODE OF COMMAND!!!
*/

# define NAME(i)		g_table[i - 1].name
# define COUNT_ARGS(i)	g_table[i - 1].args_count
# define ARG(i, j, k)	g_table[i - 1].args[j].arg[(int)k]
# define OPCODE(i) 		g_table[i].opcode
# define CODAGE(i) 		g_table[i - 1].codage
# define LABEL_SIZE(i)	g_table[i - 1].label_size

# define MAX_TABLE 16

typedef struct
{
	char				arg[3];
}						t_arr;

typedef	struct			s_table
{
	char				*name;
	char				args_count;
	t_arr				args[3];
	char				opcode;
	char				codage : 1;
	char				label_size : 4;
}						t_table;

static t_table		g_table[16] = {
	{"live", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 1, 0, 4},
	{"ld", 2, {{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}}, 2, 1, 4},
	{"st", 2, {{{1, 0, 0}}, {{1, 0, 1}}, {{0, 0, 0}}}, 3, 1, 4},
	{"add", 3, {{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}}, 4, 1, 4},
	{"sub", 3, {{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}}, 5, 1, 4},
	{"and", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 6, 1, 4},
	{"or", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 7, 1, 4},
	{"xor", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 8, 1, 4},
	{"zjmp", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 9, 0, 2},
	{"ldi", 3, {{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}}, 10, 1, 2},
	{"sti", 3, {{{1, 0, 0}}, {{1, 1, 1}}, {{1, 1, 0}}}, 11, 1, 2},
	{"fork", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 12, 0, 2},
	{"lld", 2, {{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}}, 13, 1, 4},
	{"lldi", 3, {{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}}, 14, 1, 2},
	{"lfork", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 15, 1, 2},
	{"aff", 1, {{{1, 0, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 16, 1, 4}
};

/*
** type - for codage.
** flag - flag for pointer to label.
*/

typedef struct			s_arg
{
	char				*str_value;
	int					num_value;
	char				arg_size;
	char				type;
	char				flag : 1;
	struct s_arg		*next;
}						t_arg;

/*
** bb - means bytes_before.
*/

typedef struct			s_command
{
	char				*name;
	char				opcode;
	unsigned int		bytes;
	unsigned int		bb;
	unsigned char		codage;
	t_list				*labels;
	t_arg				*args;
	struct s_command	*next;
}						t_command;

typedef struct			s_asm
{
	unsigned int		prog_size;
	unsigned int		magic;
	char				*line;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				*file_name;
	unsigned char		flag_a : 1;
	unsigned char		flag_b : 1;
	char				comment[COMMENT_LENGTH + 1];
	int					new_fd;
	int					fd;
	int					last_line_size;
	t_command			*command;
}						t_asm;

void					ft_error(char *str);
void					skip_shit(char *str, int *j, char *symbols);
void					comment_delete(char *str);
char					check_line(char *s);
int						index_of(char *needle, int len);
char					check_last_line(t_asm *asmb);
char					str_has(char *str, char flag);
char					*my_strsub(char *src, int start, int end);
char					check_last_line(t_asm *asmb);
char					str_has(char *str, char flag);
char					*my_strsub(char *src, int start, int end);
void					check_argvs(t_asm *asmb, char **av, int ac);
void					norm_file_name(char **file_name);
char					get_type(char *str);
void					get_header(t_asm *asmb);
void					get_labels(t_asm *asmb, t_command *new, int *j);
void					get_arguments(t_asm *asmb, t_command *new, int *j);
void					*get_data(char type, char *str, char *flag);
void					add_argument(t_command *command, char type,
						void *data, char flag);
unsigned int			compute_variables(t_command *command);
void					get_commands(t_asm *asmb);
void					show_bot(t_asm *asmb, t_command *command);
void					create_binary(t_asm *asmb, t_command *command);
void					disassembly_output(t_asm *asmb);
unsigned int			reverse_bytes(unsigned int x, char bytes);
t_arg					*push_new_arg(t_arg **args);
t_command				*push_new_command(t_command **head);
void					read_binary(t_asm *asmb);
char					write_t_reg(t_command *command, int i, int fd);
char					write_t_dir(t_command *command, int i, int fd);
char					write_t_ind(t_command *command, int i, int fd);

#endif
