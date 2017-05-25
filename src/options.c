/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:34:22 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/25 17:09:07 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

static int		normal_options(char c)
{
	if (c == 'l')
		g_options |= OPT_L;
	else if (c == 'R')
		g_options |= OPT_BR;
	else if (c == 'a')
		g_options |= OPT_A;
	else if (c == '1')
		g_options |= OPT_ONE;
	else if (c == '@')
		g_options |= OPT_AT;
	else if (c == 'e')
		g_options |= OPT_E;
	else if (c == 'A')
		g_options |= OPT_BA;
	else if (c == 'r')
		g_sort |= SORT_REV;
	else
		return (0);
	return (1);
}

static int		sort_options(char c)
{
	unsigned char	sort;

	sort = g_sort & SORT_REV ? SORT_REV : 0;
	if (c == 't')
		sort |= SORT_MOD;
	else if (c == 'u')
		sort |= SORT_ACC;
	else if (c == 'c')
		sort |= SORT_SC;
	else if (c == 'S')
		sort |= SORT_SIZE;
	else if (c == 'f')
	{
		sort |= SORT_NONE;
		g_options |= OPT_A;
	}
	else
		return (0);
	g_sort = sort;
	return (1);
}

static int		add_options(char *s)
{
	int		i;

	i = 1;
	if (s[i] == '-' && !(s[i + 1]))
		return (0);
	while (s[i])
	{
		if (!(normal_options(s[i])) && !(sort_options(s[i])))
		{
			ft_dprintf(2, "ft_ls: illegal option -- %c\n\
usage: ft_ls [-%s] [file ...]\n", s[i], FT_LS_OPTIONS);
			exit(0);
		}
		i++;
	}
	return (1);
}

void			get_options(int ac, char **av, int *i)
{
	g_options = 0;
	while (*i < ac && av[*i][0] == '-' && av[*i][1])
	{
		if (!(add_options(av[(*i)++])))
			break ;
	}
	if (!(ac - *i <= 1))
		g_options |= OPT_MULT;
}
