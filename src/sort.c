/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:35:59 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/20 15:25:48 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

int		ft_strrcmp(const char *s1, const char *s2)
{
	return (ft_strcmp(s1, s2) * -1);
}

int		compare_time(t_entry *t1, t_entry *t2)
{
	time_t	diff;

	diff = 0;
	if (g_sort & SORT_MOD)
		diff = t1->stats.st_mtime - t2->stats.st_mtime;
	else if (g_sort & SORT_ACC)
		diff = t1->stats.st_atime - t2->stats.st_atime;
	else if (g_sort & SORT_SC)
		diff = t1->stats.st_ctime - t2->stats.st_ctime;
	if (diff == 0)
		return (compare_path(t1, t2));
	else if (diff > 0)
		return (-1);
	return (1);
}

int		compare_size(t_entry *t1, t_entry *t2)
{
	off_t	diff;

	diff = 0;
	diff = t1->stats.st_size - t2->stats.st_size;
	if (diff == 0)
		return (compare_path(t1, t2));
	else if (diff > 0)
		return (-1);
	return (1);
}

int		compare_path(t_entry *t1, t_entry *t2)
{
	if (t1 == NULL)
		return (-1);
	else if (t2 == NULL)
		return (1);
	return (ft_strcmp(t1->name, t2->name));
}

int		none(t_entry *t1, t_entry *t2)
{
	if (t1 || t2)
		return (0);
	else
		return (0);
}
