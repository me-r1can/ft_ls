/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:05:37 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/27 17:24:39 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_buff(t_buff *buffer, int fd)
{
	buffer->fd = fd;
	buffer->pos = 0;
	ft_bzero(buffer->contents, BUFF_SIZE);
}

int		ft_putbuff(t_buff *buffer, void *contents, size_t len)
{
	size_t			ret;
	unsigned char	*c;

	c = (unsigned char *)contents;
	ret = 0;
	while (ret < len)
	{
		if ((buffer->pos) >= BUFF_SIZE)
			ft_flushbuff(buffer);
		buffer->contents[buffer->pos] = c[ret];
		++ret;
		++(buffer->pos);
	}
	return (ret);
}

void	ft_flushbuff(t_buff *buffer)
{
	write(buffer->fd, buffer->contents, buffer->pos);
	buffer->pos = 0;
	ft_bzero(buffer->contents, BUFF_SIZE);
}
