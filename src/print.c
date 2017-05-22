/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:06:34 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/22 18:15:32 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

void		column_print(t_entry *temp, t_max *max)
{
	int		pos;
	int		columns;

	pos = 0;
	columns = get_terminal_width() / (max->path + 8);
	while (temp)
	{
		if ((!(is_hidden(temp->name)) || g_options & OPT_A) ||
			(!(is_repere(temp->name)) && g_options & OPT_BA))
		{
			ft_printf("%-*s", ((max->path) + 8), temp->name);
			pos++;
		}
		if (pos == columns)
		{
			pos = 0;
			ft_printf("\n");
		}
		temp = temp->next;
	}
	if (pos < columns)
		ft_printf("\n");
}

void		line_print(t_entry *temp, t_max *max)
{
	while (temp)
	{
		ft_printf("name: %s\ttarget: %s\n", temp->name, temp->target);
		if (S_ISLNK(temp->stats.st_mode))
		{
			if (!(temp->target = ft_strnew(PATH_MAX)))
				ft_ls_error(1, 0, 0);
			readlink(temp->path, temp->target, PATH_MAX);
		}
		else
			temp->target = temp->path;
		if ((!(is_hidden(temp->name)) || g_options & OPT_A) ||
			(!(is_repere(temp->name)) && g_options & OPT_BA))
		{
			if (g_options & OPT_L)
				long_print(temp, max);
			else
				ft_printf("%s\n", temp->name);
		}
		temp = temp->next;
	}
}

void		ft_ls_print(t_entry **start, int next, int folder)
{
	t_entry		*temp;
	t_max		max;

	temp = *start;
	get_max(*start, &max);
	if (g_options & OPT_L && max.has_contents && folder)
		ft_printf("total %d\n", max.total);
	if (!(g_options & OPT_L || g_options & OPT_ONE))
		column_print(temp, &max);
	else
		line_print(temp, &max);
	if ((g_options & OPT_BR || g_options & OPT_MULT) && next)
		ft_printf("\n");
}
