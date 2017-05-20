/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 20:50:52 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/05 18:52:29 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		has_flag(t_arg *arg, char flag)
{
	if (ft_strchr(arg->flags, flag))
		return (1);
	return (0);
}

int		padding(t_buff *buffer, t_arg *arg)
{
	char		pad;
	int			width;

	pad = ' ';
	width = arg->width;
	if (width == -1)
		return (0);
	if (arg->len > arg->width)
		return (0);
	if (has_flag(arg, '0') && !(has_flag(arg, '-')))
	{
		if (!(is_number(arg->type)))
			pad = '0';
		else if ((arg->precision == -1 || arg->precision > arg->width))
			pad = '0';
	}
	while (--width >= arg->len)
		ft_putbuff(buffer, &pad, 1);
	return (arg->width - arg->len);
}

int		print(t_buff *buffer, t_arg *arg, int count)
{
	int		*n;

	if (arg->type == 0)
		return (0);
	if (arg->type == 'n')
	{
		if ((n = (int *)arg->target))
			*n = count;
		return (0);
	}
	if (arg->type == 'p')
	{
		arg->length_flag = l;
		add_flag(arg, '#');
	}
	if (arg->type == 's')
		return (ft_printstr(buffer, arg));
	if (is_number(arg->type))
		return (ft_printnbr(buffer, arg));
	return (ft_printchar(buffer, arg));
}
