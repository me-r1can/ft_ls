/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 21:15:50 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/05 16:50:02 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_precision(const char *restrict format, t_arg *ret,
	va_list args, int *i)
{
	int		temp;

	++(*i);
	if (format[*i] == '*')
	{
		if (!(temp = va_arg(args, int)))
			temp = 0;
		if (ret->precision == -1)
			ret->precision = temp;
	}
	else if (ft_isdigit(format[*i]))
	{
		ret->precision = ft_atoi_inplace(format, i);
		--(*i);
	}
	else
	{
		ret->precision = 0;
		--(*i);
	}
	if (ret->precision < -1)
		ret->precision = -1;
}

void	check_width(const char *restrict format, t_arg *ret,
	va_list args, int *i)
{
	if (format[*i] == '*')
	{
		if (!(ret->width = va_arg(args, int)))
			ret->width = -1;
	}
	else
	{
		ret->width = ft_atoi_inplace(format, i);
		(*i)--;
	}
	if (ret->width < -1)
	{
		add_flag(ret, '-');
		ret->width *= -1;
	}
}

void	add_flag(t_arg *ret, char f)
{
	if (!(ft_strchr(ret->flags, f)))
		ret->flags[(ret->flag_count)++] = f;
}

void	add_length_flag(t_arg *ret, char f)
{
	if (!(ret->length_flag + f > 216))
		ret->length_flag = ret->length_flag + (int)f;
}

void	convert_caps(t_arg *ret)
{
	if (!(ft_strchr(FT_PRINTF_TYPES, ret->type)))
		ret->length_flag = 0;
	else if (ret->type != 'X' && (ret->type >= 'A' && ret->type <= 'Z'))
	{
		ret->length_flag = l;
		ret->type = ft_tolower(ret->type);
	}
}
