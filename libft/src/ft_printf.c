/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:02:15 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/27 17:24:17 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vdprintf(int fd, const char *restrict format, va_list ap)
{
	int			i;
	t_arg		current;
	t_buff		buffer;
	int			ret;

	i = 0;
	ret = 0;
	initialize_buff(&buffer, fd);
	while (format[i])
	{
		if (format[i] == '%')
		{
			initialize_arg(&current);
			if (i += new_arg(format, ap, i, &current))
				ret += print(&buffer, &current, ret);
		}
		else
			ret += ft_putbuff(&buffer, (void *)&(format[i]), 1);
		i++;
	}
	ft_flushbuff(&buffer);
	return (ret);
}

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list		ap;

	if (fd < 0)
		return (0);
	va_start(ap, format);
	return (ft_vdprintf(fd, format, ap));
	va_end(ap);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;

	va_start(ap, format);
	return (ft_vdprintf(1, format, ap));
	va_end(ap);
}
