/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:21:23 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/03 14:22:33 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printnstr(t_buff *buffer, t_arg *arg)
{
	char		*str;
	int			ret;

	ret = 0;
	str = (char *)arg->target;
	arg->len = ft_strlen(str);
	if (arg->precision != -1 && arg->precision < arg->len)
		arg->len = arg->precision;
	if (has_flag(arg, '-'))
	{
		ret += ft_putbuff(buffer, str, arg->len);
		ret += padding(buffer, arg);
	}
	else
	{
		ret += padding(buffer, arg);
		ret += ft_putbuff(buffer, str, arg->len);
	}
	return (ret);
}

int		ft_printnchar(t_buff *buffer, char c)
{
	return (ft_putbuff(buffer, &c, 1));
}

int		ft_printchar(t_buff *buffer, t_arg *arg)
{
	int		ret;

	ret = 0;
	arg->len = 1;
	if (!(has_flag(arg, '-')))
		ret += padding(buffer, arg);
	if (arg->type == '%')
		ret += ft_printnchar(buffer, '%');
	else if (arg->length_flag == l)
		ret += ft_printwchar(buffer, (wchar_t)arg->target);
	else if (!(ft_strchr(FT_PRINTF_TYPES, arg->type)))
		ret += ft_printnchar(buffer, arg->type);
	else
		ret += ft_printnchar(buffer, (char)arg->target);
	if (has_flag(arg, '-'))
		ret += padding(buffer, arg);
	return (ret);
}

int		ft_printstr(t_buff *buffer, t_arg *arg)
{
	if (!(arg->target))
		arg->target = "(null)";
	if (arg->length_flag == l)
		return (ft_printwstr(buffer, arg));
	return (ft_printnstr(buffer, arg));
}
