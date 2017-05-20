/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:39:43 by nlowe             #+#    #+#             */
/*   Updated: 2017/04/03 14:53:53 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_hex(char c)
{
	if (c == 'X' || c == 'x' || c == 'p')
		return (1);
	return (0);
}

int		is_oct(char c)
{
	if (c == 'o' || c == 'O')
		return (1);
	return (0);
}

int		is_dec(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'I' || c == 'u' || c == 'U')
		return (1);
	return (0);
}

int		is_number(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'x'
		|| c == 'X' || c == 'p' || c == 'b')
		return (1);
	return (0);
}
