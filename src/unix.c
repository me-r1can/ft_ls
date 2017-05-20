/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unix.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 23:20:13 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/20 15:29:21 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		recent(t_stat *stats)
{
	time_t		diff;
	time_t		max_diff;

	max_diff = 3600 * 24 * 30.5 * 6;
	diff = time(0) - stats->st_mtime;
	if (diff > max_diff || diff < -max_diff)
		return (0);
	if (diff < 0)
		return (-1);
	return (1);
}

int		is_device(t_stat *stats)
{
	if (S_ISBLK(stats->st_mode) || S_ISCHR(stats->st_mode))
		return (1);
	return (0);
}

int		is_repere(char *path)
{
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0)
		return (1);
	return (0);
}

int		is_hidden(char *path)
{
	if (!(path[0]))
		return (0);
	if (path[0] == '.')
		return (1);
	return (0);
}

int		get_terminal_width(void)
{
	struct winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	return ((int)window.ws_col);
}
