/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:13:12 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/27 17:23:33 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include "libft.h"

# define BUFF_SIZE 64
# define FT_PRINTF_FLAGS "#0-+ $'"
# define FT_PRINTF_TYPES "sSpdDioOuUxXcCnb"
# define FT_PRINTF_LENGTH "hljz"
# define HEX "0123456789ABCDEF"
# define SMALL_HEX "0123456789abcdef"
# define MAX_INT_SIZE 50
# define MAX_WCHAR 0x10FFFF

typedef enum		e_length
{
	none = 0,
	h = 104,
	j = 106,
	l = 108,
	z = 122,
	hh = 208,
	ll = 216
}					t_length;

typedef struct		s_arg
{
	char			flags[10];
	int				flag_count;
	t_length		length_flag;
	int				width;
	int				len;
	int				precision;
	int				base;
	int				sign;
	char			type;
	void			*target;
	wchar_t			*widestr;
}					t_arg;

typedef struct		s_buff
{
	unsigned char	contents[BUFF_SIZE];
	size_t			pos;
	int				fd;
}					t_buff;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *restrict format, ...);

int					ft_putbuff(t_buff *buffer, void *contents, size_t len);
void				ft_flushbuff(t_buff *buffer);
void				initialize_buff(t_buff *buffer, int fd);

int					print(t_buff *buffer, t_arg *arg, int count);
int					padding(t_buff *buffer, t_arg *arg);
int					has_flag(t_arg *arg, char flag);
void				add_flag(t_arg *ret, char f);
void				add_length_flag(t_arg *ret, char f);
void				initialize_arg(t_arg *ret);
int					new_arg(const char *restrict format, va_list args,
	int i, t_arg *current);

void				check_precision(const char *restrict format, t_arg *ret,
	va_list args, int *i);
void				check_width(const char *restrict format, t_arg *ret,
	va_list args, int *i);
void				convert_caps(t_arg *ret);

unsigned long long	get_negative(t_arg *arg);
int					get_base(t_arg *arg);
long long			signed_convert(t_arg *arg);
unsigned long long	unsigned_convert(t_arg *arg);

int					ft_printstr(t_buff *buffer, t_arg *arg);
int					ft_printchar(t_buff *buffer, t_arg *arg);
int					ft_printwchar(t_buff *buffer, wchar_t c);
size_t				ft_wcslen(wchar_t *s, int precision);
int					ft_printwstr(t_buff *buffer, t_arg *arg);

int					ft_printnbr(t_buff *buffer, t_arg *arg);

int					ft_printptr(t_buff *buffer, t_arg *arg);

int					is_hex(char c);
int					is_oct(char c);
int					is_dec(char c);
int					is_number(char c);

#endif
