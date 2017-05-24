/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:35:59 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/24 22:31:03 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

int		timecmp(const char *t1, const char *t2)
{
	time_t	diff;
	t_stat	t1_stats;
	t_stat	t2_stats;
	int		rev;

	diff = 0;
	rev = (g_sort & SORT_REV) ? -1 : 1;
	if (lstat(t1, &t1_stats) != 0 || lstat(t2, &t2_stats) != 0)
		diff = 0;
	else if (g_sort & SORT_MOD)
		diff = t1_stats.st_mtime - t2_stats.st_mtime;
	else if (g_sort & SORT_ACC)
		diff = t1_stats.st_atime - t2_stats.st_atime;
	else if (g_sort & SORT_SC)
		diff = t1_stats.st_ctime - t2_stats.st_ctime;
	if (diff == 0)
		return (ft_strcmp(t1, t2) * rev);
	else if (diff > 0)
		return (-1 * rev);
	return (1 * rev);
}

int		sizecmp(const char *t1, const char *t2)
{
	off_t	diff;
	t_stat	t1_stats;
	t_stat	t2_stats;
	int		rev;

	diff = 0;
	rev = (g_sort & SORT_REV) ? -1 : 1;
	if (lstat(t1, &t1_stats) != 0 || lstat(t2, &t2_stats) != 0)
		diff = 0;
	else
		diff = t1_stats.st_size - t2_stats.st_size;
	if (diff == 0)
		return (ft_strcmp(t1, t2) * rev);
	else if (diff > 0)
		return (-1 * rev);
	return (1 * rev);
}