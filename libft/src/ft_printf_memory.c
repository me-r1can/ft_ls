/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:52:15 by nlowe             #+#    #+#             */
/*   Updated: 2017/03/20 17:26:11 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printptr(t_buff *buffer, t_arg *arg)
{
	unsigned char	*ptr;
	int				ret;
	unsigned char	out[2];

	ret = 0;
	ptr = (unsigned char *)arg->target;
	while (*ptr)
	{
		out[0] = HEX[*ptr / 16];
		out[1] = HEX[*ptr % 16];
		ret += ft_putbuff(buffer, out, 2);
		ptr++;
	}
	return (ret);
}
