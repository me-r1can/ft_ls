/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:52:56 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/05 16:48:43 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_wcsize(int c)
{
	int		len;

	len = 0;
	if (c < 0)
		c *= -1;
	while (c >> len)
		++len;
	return (len);
}

size_t			ft_wcslen(wchar_t *s, int precision)
{
	size_t	len;
	size_t	prev;

	len = 0;
	while (*s && (precision == -1 || len <= (size_t)precision))
	{
		prev = len;
		len += (ft_wcsize(*s) / 4);
		s++;
	}
	if (len <= (size_t)precision)
		return (len);
	return (prev);
}

static void		convert_unicode(wchar_t c, char *bits, int *i, int len)
{
	if (len >= 8)
	{
		if (len >= 12)
		{
			if (len > 16)
			{
				bits[(*i)++] = (((c >> 18) & 0b00000111) | 0b11110000);
				bits[(*i)++] = (((c >> 12) & 0b00111111) | 0b10000000);
			}
			else
				bits[(*i)++] = (((c >> 12) & 0b00011111) | 0b11100000);
			bits[(*i)++] = (((c >> 6) & 0b00111111) | 0b10000000);
		}
		else
			bits[(*i)++] = (((c >> 6) & 0b00011111) | 0b11000000);
		bits[(*i)++] = ((c & 0b00111111) | 0b10000000);
	}
	else
		bits[(*i)++] = (unsigned char)c;
}

int				ft_printwchar(t_buff *buffer, wchar_t c)
{
	char	bits[5];
	int		i;
	int		len;

	if (c < 0 || c > MAX_WCHAR)
		return (0);
	ft_bzero(bits, 5);
	i = 0;
	len = ft_wcsize(c);
	convert_unicode(c, bits, &i, len);
	return (ft_putbuff(buffer, bits, i));
}

int				ft_printwstr(t_buff *buffer, t_arg *arg)
{
	int			ret;
	int			i;

	ret = 0;
	i = 0;
	if (!(arg->widestr))
	{
		arg->length_flag = 0;
		return (ft_printstr(buffer, arg));
	}
	arg->len = ft_wcslen(arg->widestr, arg->precision);
	if (!(has_flag(arg, '-')))
		ret += padding(buffer, arg);
	while (*(arg->widestr) && i < (int)(arg->len))
	{
		i += ft_printwchar(buffer, *(arg->widestr));
		(arg->widestr)++;
	}
	ret += i;
	if (has_flag(arg, '-'))
		ret += padding(buffer, arg);
	return (ret);
}
