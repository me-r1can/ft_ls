/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:02:43 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/25 15:50:13 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned char g_options;
unsigned char g_sort;

int		main(int ac, char **av)
{
	t_list			*queue;

	queue = NULL;
	parse(ac, av, &queue);
	ft_ls(&queue, 0);
	return (0);
}
