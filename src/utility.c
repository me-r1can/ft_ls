/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:04:07 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/20 15:33:52 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

int			ft_ls_error(int quit, const char *name, int arnaud)
{
	if (name && !(*name))
	{
		name = "fts_open";
		quit = 1;
	}
	if (name && arnaud)
		ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(arnaud));
	else if (arnaud)
		ft_dprintf(2, "ft_ls: %s\n", strerror(arnaud));
	else if (name)
		ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno));
	else
		perror("ft_ls");
	if (quit)
		exit(0);
	return (1);
}

char		*get_full_path(char *active, char *parent, char *file)
{
	if (!active || !parent || !file)
		return (NULL);
	ft_strncpy(active, parent, PATH_MAX);
	if (active[ft_strlen(active) - 1] != '/')
		ft_strlcat(active, "/", PATH_MAX);
	ft_strlcat(active, file, PATH_MAX);
	return (active);
}

int			ft_numlen(long long nbr)
{
	int		len;

	if (nbr == 0)
		return (1);
	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}
