/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 21:55:06 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/05 16:36:04 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_negative(t_arg *arg)
{
	long long			l;

	arg->sign = 1;
	if (arg->target == NULL)
		return (0);
	if ((arg->type == 'd' || arg->type == 'i'))
	{
		l = signed_convert(arg);
		if (l < 0)
		{
			arg->sign = -1;
			if (l < -9223372036854775807)
				return (9223372036854775808ULL);
			l *= -1;
		}
		return ((unsigned long long)l);
	}
	return ((unsigned long long)unsigned_convert(arg));
}

int					get_base(t_arg *arg)
{
	if (is_hex(arg->type))
		return (16);
	if (is_oct(arg->type))
		return (8);
	if (arg->type == 'b' || arg->type == 'B')
		return (2);
	return (10);
}

long long			signed_convert(t_arg *arg)
{
	if (arg->length_flag == hh)
		return ((char)arg->target);
	if (arg->length_flag == h)
		return ((short)arg->target);
	if (arg->length_flag == l)
		return ((long)arg->target);
	if (arg->length_flag == ll)
		return ((long long)arg->target);
	if (arg->length_flag == j)
		return ((uintmax_t)arg->target);
	if (arg->length_flag == z)
		return ((size_t)arg->target);
	if (arg->length_flag == h)
		return ((short)arg->target);
	return ((int)arg->target);
}

unsigned long long	unsigned_convert(t_arg *arg)
{
	if (arg->length_flag == hh)
		return ((unsigned char)arg->target);
	if (arg->length_flag == h)
		return ((unsigned short)arg->target);
	if (arg->length_flag == l)
		return ((unsigned long)arg->target);
	if (arg->length_flag == ll)
		return ((unsigned long long)arg->target);
	if (arg->length_flag == j)
		return ((intmax_t)arg->target);
	if (arg->length_flag == z)
		return ((size_t)arg->target);
	if (arg->length_flag == h)
		return ((unsigned short)arg->target);
	return ((unsigned int)arg->target);
}
