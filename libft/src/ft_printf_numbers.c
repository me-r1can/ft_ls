/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 21:19:04 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/05 16:55:19 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbrlen(unsigned long long nbr, int base)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

int		ft_setnbr(t_buff *buffer, t_arg *arg, int len,
	unsigned long long nbr)
{
	char				out[MAX_INT_SIZE];
	int					i;

	ft_memset(out, '0', MAX_INT_SIZE);
	if (len <= 0)
		return (0);
	i = len - 1;
	while (nbr != 0 && i >= 0)
	{
		if (arg->type == 'X' || arg->type == 'O')
			out[i--] = HEX[nbr % arg->base];
		else
			out[i--] = SMALL_HEX[nbr % arg->base];
		nbr /= arg->base;
	}
	return (ft_putbuff(buffer, out, len));
}

int		ft_printsign(t_buff *buffer, t_arg *arg, unsigned long long nbr,
	int print)
{
	char	ret[4];
	int		i;

	i = 0;
	if (arg->sign == -1)
		ret[i++] = '-';
	else if (arg->sign == 1 && is_dec(arg->type) && arg->type != 'u')
	{
		if (has_flag(arg, '+'))
			ret[i++] = '+';
		else if (has_flag(arg, ' '))
			ret[i++] = ' ';
	}
	if ((has_flag(arg, '#') && !(is_dec(arg->type)) &&
		(nbr != 0 || (arg->precision == 0 && is_oct(arg->type))))
		|| arg->type == 'p')
	{
		ret[i++] = '0';
		if (arg->type == 'p')
			ret[i++] = 'x';
		else if (is_hex(arg->type))
			ret[i++] = arg->type;
	}
	return (print ? ft_putbuff(buffer, ret, i) : i);
}

void	precision(t_arg *arg, int *digits, unsigned long long nbr)
{
	if (arg->precision != -1 && arg->precision > *digits)
	{
		*digits = arg->precision;
		if (is_oct(arg->type) && has_flag(arg, '#'))
			*digits -= 1;
	}
	if (nbr == 0 && arg->precision == 0)
		*digits = 0;
	arg->len = *digits;
}

int		ft_printnbr(t_buff *buffer, t_arg *arg)
{
	int					ret;
	int					digits;
	unsigned long long	nbr;

	ret = 0;
	nbr = get_negative(arg);
	arg->base = get_base(arg);
	digits = ft_nbrlen(nbr, arg->base);
	precision(arg, &digits, nbr);
	arg->len += ft_printsign(buffer, arg, nbr, 0);
	if (has_flag(arg, '0'))
		ret += ft_printsign(buffer, arg, nbr, 1);
	if (!(has_flag(arg, '-')))
		ret += padding(buffer, arg);
	if (!(has_flag(arg, '0')))
		ret += ft_printsign(buffer, arg, nbr, 1);
	ret += ft_setnbr(buffer, arg, digits, nbr);
	if (has_flag(arg, '-'))
		ret += padding(buffer, arg);
	return (ret);
}
