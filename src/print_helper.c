/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 23:26:40 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/20 15:28:05 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

static void		initialize_max(t_max *max)
{
	max->has_contents = 0;
	max->total = 0;
	max->links = 0;
	max->uid = 0;
	max->gid = 0;
	max->size = 0;
	max->path = 0;
	max->major = 0;
	max->minor = 0;
}

static t_max	get_field_len(t_entry *temp)
{
	t_max	current;

	initialize_max(&current);
	current.links = ft_numlen(temp->stats.st_nlink);
	current.uid = ft_strlen(temp->usr->pw_name);
	current.gid = ft_strlen(temp->grp->gr_name);
	current.path = ft_strlen(temp->name);
	if (is_device(&(temp->stats)))
	{
		current.major = ft_numlen(MAJOR(temp->stats.st_rdev));
		current.minor = ft_numlen(MINOR(temp->stats.st_rdev));
	}
	else
		current.size = ft_numlen(temp->stats.st_size);
	return (current);
}

static void		compare_max(int value, int *max)
{
	if (value > *max)
		*max = value;
}

static void		compare_all(t_max *current, t_max *max)
{
	compare_max(current->links, &(max->links));
	compare_max(current->uid, &(max->uid));
	compare_max(current->gid, &(max->gid));
	compare_max(current->size, &(max->size));
	compare_max(current->path, &(max->path));
	compare_max(current->major, &(max->major));
	compare_max(current->minor, &(max->minor));
}

void			get_max(t_entry *start, t_max *max)
{
	t_entry		*temp;
	t_max		current;

	initialize_max(max);
	temp = start;
	while (temp)
	{
		if ((!(is_hidden(temp->name)) || g_options & OPT_A) ||
		(!(is_repere(temp->name)) && g_options & OPT_BA))
		{
			temp->usr = getpwuid(temp->stats.st_uid);
			temp->grp = getgrgid(temp->stats.st_gid);
			max->total += temp->stats.st_blocks;
			max->has_contents = 1;
			current = get_field_len(temp);
			compare_all(&current, max);
		}
		temp = temp->next;
	}
	if (max->major + max->minor > max->size)
		max->size = (max->major + max->minor + 2);
}
