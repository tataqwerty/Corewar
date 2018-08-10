/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:40:45 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/14 15:34:01 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>

# define BUFF_SIZE 42

# define EOC "\e[0m"
# define RED "\e[91m"
# define GREEN "\e[92m"
# define YELLOW "\e[93m"
# define BLUE "\e[94m"
# define PINK "\e[95m"
# define WHITE "\e[97m"

# define TYPE pf->type
# define MODF pf->modifier
# define SPACE pf->space
# define HASH pf->hash
# define PLUS pf->plus
# define MINUS pf->minus
# define ZERO pf->zero
# define DOT pf->dot
# define PREC pf->precision
# define WIDTH pf->width
# define BUFFER pf->buffer
# define N pf->n
# define N_UNI pf->n_uni

typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_strtrim(char **s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(int c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(int c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t			ft_lstlen(t_list *list);
void			ft_lstprint(t_list *list);
void			ft_stralldel(char **str, size_t n);
size_t			ft_count_words(char *str, char c);
size_t			ft_count(intmax_t n, short int base);
size_t			ft_sqrt(size_t n);
int				get_next_line(const int fd, char **line);
char			*ft_strjoinfree(char const *s1, char const *s2, char n);
void			ft_list_pushback(t_list **head, char *line);
char			ft_is_uint(char *str);

/*
** ****************************************************************************
** ***************************** FT_PRINTF ************************************
** ****************************************************************************
*/

typedef struct	s_str
{
	char		type;
	char		space;
	char		plus;
	char		minus;
	char		zero;
	char		dot;
	char		hash;
	char		modifier[3];
	int			precision;
	int			width;
	char		buffer[42];
	int			n;
	int			symbols;
	int			n_uni;
}				t_str;

int				ft_printf(const char *format, ...);
int				check_percent(va_list ap, const char *format, t_str *pf);
int				write_type_x_p(va_list ap, t_str *pf);
int				write_type_d_i(va_list ap, t_str *pf);
int				write_type_o(va_list ap, t_str *pf);
int				write_type_u(va_list ap, t_str *pf);
int				write_type_c(va_list ap, t_str *pf);
int				write_type_s(va_list ap, t_str *pf);
void			write_symbol_s_uni(t_str *pf, wchar_t *str_uni, int n);
void			write_to_buffer(t_str *pf, int c);
void			write_space_to_buffer(t_str *pf);
int				write_colors(const char *format, t_str *pf);
void			check_buffer(t_str *pf, int turn_off, int clean_pf);
void			ft_cpy_to_buffer(t_str *pf, unsigned char *code, int len);
void			ft_putnbr_base(intmax_t n, short int base, char big, t_str *pf);
void			ft_unputnbr_base(uintmax_t n, short int base,
											char big, t_str *pf);
uintmax_t		check_modifier_un_int(va_list ap, t_str *pf);

#endif
