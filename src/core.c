/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:29:40 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/23 20:59:54 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

t_entry			*get_contents(char *parent, t_list **queue, char *current)
{
	t_entry		*new;

	if (!(new = new_entry()))
		ft_ls_error(1, 0, 0);
	new->name = ft_strdup(current);
	get_full_path(new->path, parent, new->name);
	if (lstat(new->path, new->stats) != 0)
		ft_ls_error(0, new->path, errno);
	if ((g_options & OPT_BR || g_sort & SORT_MOD) && queue)
	{
		if (!(is_repere(new->name)) && (g_options & OPT_BR) &&
			S_ISDIR(new->stats->st_mode) && ((new->name)[0] != '.' ||
				(g_options & OPT_A)))
			add_to_queue(queue, new->path);
	}
	return (new);
}

t_entry			*get_dir(char *path, t_list **queue)
{
	t_entry		*start;
	t_dir		*current;
	DIR			*dir;

	start = NULL;
	if ((g_options & OPT_BR && !(is_repere(path))) || g_options & OPT_MULT)
		ft_printf("%s:\n", path);
	if (!(dir = opendir(path)))
	{
		ft_ls_error(0, ((ft_strrchr(path, '/') + 1) ?
			(ft_strrchr(path, '/') + 1) : path), 0);
		if ((g_options & OPT_BR || g_options & OPT_MULT) && *queue)
			ft_printf("\n");
		return (NULL);
	}
	while ((current = readdir(dir)) != NULL)
		ft_insert(&start, get_contents(path, queue, current->d_name));
	closedir(dir);
	return (start);
}

int				ft_ls(t_list **queue)
{
	t_entry			*folder;
	t_list			*temp;
	t_list			*free_queue;

	temp = *queue;
	folder = NULL;
	while (temp)
	{
		if ((folder = get_dir((char *)temp->content, &(temp->next))))
		{
			ft_ls_print(&folder, (temp->next ? 1 : 0), 1);
			free_list(&folder);
		}
		free_queue = temp;
		temp = temp->next;
		free(free_queue->content);
		free(free_queue);
	}
	return (1);
}
