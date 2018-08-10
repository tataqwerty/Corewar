/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:45:19 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/11 13:45:23 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "error.h"
# include <fcntl.h>
# include <time.h>
# include <curses.h>
# include <signal.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/select.h>
# include <pthread.h>

# define T_REG_SIZE				1
# define T_DIR_SIZE				2
# define T_IND_SIZE				2

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define T_IND_READ				4

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
*******************************************************************************
****************************** TABLE OF COMMANDS ******************************
*******************************************************************************
*/

# define NAME(i)				g_table[i - 1].name
# define COUNT_ARGS(i)			g_table[i - 1].args_count
# define ARG(i, j, k)			g_table[i - 1].args[j].arg[(int)k]
# define OPCODE(i)				g_table[i].opcode
# define CODAGE(i)				g_table[i - 1].codage
# define LABEL_SIZE(i)			g_table[i - 1].label_size
# define PREFORM(i)				g_table[i - 1].cycles
# define MAX_TABLE 				16

typedef struct			s_arr
{
	char				arg[3];
}						t_arr;

typedef	struct			s_table
{
	char				*name;
	char				args_count;
	t_arr				args[3];
	char				opcode;
	unsigned char		codage : 1;
	unsigned char		label_size : 4;
	unsigned int		cycles;
}						t_table;

static t_table			g_table[16] = {
	{"live", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 1, 0, 4, 10},
	{"ld", 2, {{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}}, 2, 1, 4, 5},
	{"st", 2, {{{1, 0, 0}}, {{1, 0, 1}}, {{0, 0, 0}}}, 3, 1, 4, 5},
	{"add", 3, {{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}}, 4, 1, 4, 10},
	{"sub", 3, {{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}}, 5, 1, 4, 10},
	{"and", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 6, 1, 4, 6},
	{"or", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 7, 1, 4, 6},
	{"xor", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 8, 1, 4, 6},
	{"zjmp", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 9, 0, 2, 20},
	{"ldi", 3, {{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}}, 10, 1, 2, 25},
	{"sti", 3, {{{1, 0, 0}}, {{1, 1, 1}}, {{1, 1, 0}}}, 11, 1, 2, 25},
	{"fork", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 12, 0, 2, 800},
	{"lld", 2, {{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}}, 13, 1, 4, 10},
	{"lldi", 3, {{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}}, 14, 1, 2, 50},
	{"lfork", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 15, 1, 2, 1000},
	{"aff", 1, {{{1, 0, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 16, 1, 4, 2}
};

/*
*****************************************************************************
*****************************************************************************
*/

typedef struct s_win	t_win;

/*
** exec - executable
** lives_cur_period - Quantity of lives for current period.
** lives_last_period - Quantity of lives for last period.
** last_live - Cycle on which this bot has executed shout his player/id/name.
*/

typedef struct			s_bot
{
	unsigned char		player_counter;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		*exec;
	unsigned int		id;
	unsigned int		size;
	unsigned int		lives_cur_period;
	unsigned int		lives_last_period;
	unsigned int		last_live;
	unsigned int		bot_processes_lives;
	struct s_bot		*next;
}						t_bot;

/*
** position - INDEX
*/

typedef struct			s_process
{
	unsigned int		position;
	unsigned char		carry : 1;
	unsigned char		live : 1;
	unsigned int		registries[REG_NUMBER + 1];
	unsigned char		opcode;
	unsigned char		codage;
	unsigned int		cycles_to_perform;
	t_bot				*parent;
	struct s_process	*next;
}						t_process;

/*
** dump_cycles - Cycle on which we are going to dump memory.
** cur_cycle - Current cycle.
** process_count - Quantity of all processes on map.
** *win_link - link to the window of ncurses,
** initialises if flag_visual == 1
** *process - All processes.
*/

typedef struct			s_vm
{
	unsigned char		count_players;
	unsigned char		flag_visual : 1;
	unsigned char		flag_dump : 1;
	unsigned char		flag_server : 1;
	unsigned char		flag_client : 1;
	unsigned int		cycle_to_die;
	unsigned int		dump_cycles;
	unsigned int		cur_cycle;
	unsigned int		last_change_cycle_to_die;
	unsigned int		future_die;
	unsigned int		process_count;
	unsigned int		port;
	char				*ip;
	t_win				*win_link;
	t_bot				*winner;
	t_process			*process;
	t_bot				*bot;
	t_bot				*last_live_bot;
}						t_vm;

/*
** counter - How much iterations this pixel must be in bold.
*/

typedef struct			s_pixel
{
	unsigned char		counter;
	unsigned char		color;
}						t_pixel;

t_pixel					**g_pixels;
unsigned char			g_map[MEM_SIZE];
t_vm					*g_vm;

void					ft_error(char *s);
void					usage(void);
unsigned int			get_arg(unsigned int i, char arg_size);
unsigned int			reverse_bytes(unsigned int data, char bytes);
char					get_arg_size(char opcode, char type);
void					decipher_codage(char *arr,
						unsigned char n_args, unsigned char codage);
void					pseudo_codage(char *arr, char opcode);
void					get_info_server(char *args[], int argv, int *i);
void					get_info_client(char *args[], int argv, int *i);
t_process				*push_new_process(t_process **head, unsigned int
						*process_count, t_bot *parent, unsigned int position);
void					check_magic_header(int fd);
void					bot_parsing(int fd, t_bot *new);
t_bot					*push_new_bot(t_bot **head, unsigned int id);
void					sort_bot_list(t_bot **head,
						unsigned char count_players);
void					parse_argument(int count, char **args, int *i);
void					get_args(int argc, char **args);
int						step(void);
void					fill_map(void);

/*
** Process functions
*/

# define GET_CODAGE		get_arg((process->position + 1) % MEM_SIZE, 1)

int						check_valid_codage(char opcode, char *codage);
void					change_process_position(char opcode, char *codage,
						t_process *process);
void					set_map_value(t_process *process, unsigned int val,
						unsigned int new_pstn);
void					ft_live(t_process *process);
void					ft_ld(t_process *process);
void					ft_st(t_process *process);
void					ft_add(t_process *process);
void					ft_sub(t_process *process);
void					ft_and(t_process *process);
void					ft_or(t_process *process);
void					ft_xor(t_process *process);
void					ft_zjmp(t_process *process);
void					ft_ldi(t_process *process);
void					ft_sti(t_process *process);
void					ft_fork(t_process *process);
void					ft_lld(t_process *process);
void					ft_lldi(t_process *process);
void					ft_lfork(t_process *process);
void					ft_aff(t_process *process);

static void				(*g_func[16])(t_process *process) = {
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor,
	ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff
};

/*
********************************************************************************
****************************** TEXT OUTPUT MODE ********************************
********************************************************************************
*/

void					print_header(void);
void					dump_print(void);
void					print_winer(void);
void					text_out(void);

/*
********************************************************************************
***************************** NCURSES OUTPUT MODE ******************************
********************************************************************************
*/

/*
** CURSOR
*/

# define CURSOR_X 		win->cursor_x
# define CURSOR_Y 		win->cursor_y

/*
** A starting point of cursor
*/

# define X_BEGIN		3
# define Y_BEGIN		2

/*
** UI keys
*/

# define KEY_Q			113
# define KEY_W			119
# define KEY_E			101
# define KEY_R			114
# define KEY_S			115
# define KEY_SPACE		32
# define RESIZE			410

/*
** Attributes ON / OFF
*/

# define ON				1
# define OFF			2

/*
** Statistics for current period / last_period
*/

# define CURR_PERIOD 	1
# define LAST_PERIOD 	2

# define INIT_PIXEL_COLOR 5

# define PX_CLR g_pixels[process->position]->color
# define PX_CNTR g_pixels[process->position]->counter

# define TURN_ON_LIVE ((PX_CLR = ((PX_CLR) % 10) + 10)&&(PX_CNTR = 50)) ? 1 : 0

# define TURN_ON_PROCESS PX_CLR = (PX_CLR % 10) + 20
# define SET_PIXEL_COLOR PX_CLR = PX_CLR % 10

# define SPEED (unsigned long)(CLOCKS_PER_SEC / win->speed)

struct					s_win
{
	WINDOW				*window;
	int					height;
	int					width;
	int					sidebar_pad;
	int					cursor_y;
	int					cursor_x;
	short int			speed;
	unsigned char		paused : 1;
};

void					visualize(void);
void					client_visualize(int socket_fd, fd_set read_fds);
void					print_winner(t_win *win);
t_win					*init_win(void);
void					create_pixel_map(void);
void					color_preparation(void);
void					prepare_window(t_win *win);
void					draw_map(t_win *win);
void					redraw(t_win *win);
void					show_sidebar(t_win *win);
void					sidebar_statistics(t_win *win);
void					show_status(t_win *win);
void					fill_pixel_map(void);
void					handle_pixels(void);

/*
********************************************************************************
****************************** NETWORK GAME MODE *******************************
********************************************************************************
*/

# define PORT 8888

typedef struct			s_server
{
	int					master_socket;
	int					client_sockets[4];
	unsigned char		n_client_sockets;
	unsigned char		flag_start;
	fd_set				read_fds;
}						t_server;

void					client(void);
int						create_socket(void);
void					foreach_sockets(t_server *server, unsigned char *str,
						int bytes);
void					get_data_select(int socket_fd,
						fd_set read_fds, void *dest, int len);
void					server(void);
void					dispatcher_sockets(t_server *server);
void					get_clients(t_server *server);
void					get_clients_exec(t_server *server);
void					get_game(int socket_fd, fd_set read_fds);
void					send_data_all_clients(t_server *server);
void					get_data_from_server(int socket_fd, fd_set read_fds);

#endif
