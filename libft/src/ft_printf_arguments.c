/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 21:17:52 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/05 18:17:30 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		initialize_arg(t_arg *ret)
{
	ft_strclr(ret->flags);
	ret->flag_count = 0;
	ret->length_flag = none;
	ret->width = -1;
	ret->len = 0;
	ret->precision = -1;
	ret->type = 0;
	ret->target = NULL;
	ret->widestr = NULL;
}

static int	parse(const char *restrict format, va_list args, int *i, t_arg *ret)
{
	if (ft_strchr(FT_PRINTF_FLAGS, format[*i]))
		add_flag(ret, format[*i]);
	else if (format[*i] == '*' || (ft_isdigit(format[*i]) && format[*i] != '0'))
		check_width(format, ret, args, i);
	else if (ft_strchr(FT_PRINTF_LENGTH, format[*i]))
		add_length_flag(ret, format[*i]);
	else if (format[*i] == '.')
		check_precision(format, ret, args, i);
	else
		return (0);
	return (1);
}

int			new_arg(const char *restrict format, va_list args,
	int start, t_arg *ret)
{
	int		i;

	if (!(format[start + 1]))
		return (0);
	i = start + 1;
	while (!(ft_strchr(FT_PRINTF_TYPES, format[i])) &&
		parse(format, args, &i, ret))
		++i;
	ret->type = (format[i] ? format[i] : format[i - 1]);
	convert_caps(ret);
	if (ret->type == 's' && ret->length_flag >= l)
		ret->widestr = va_arg(args, wchar_t *);
	else if (ft_strchr(FT_PRINTF_TYPES, ret->type))
		ret->target = va_arg(args, void *);
	return (i - start);
}
