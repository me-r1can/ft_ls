/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:29:40 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/24 21:18:41 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

t_entry			*get_contents(char *parent, t_list **queue, char *current, int *recursive)
{
	t_entry		*new;

	if (!(new = new_entry()))
		ft_ls_error(1, 0, 0);
	new->name = ft_strdup(current);
	get_full_path(new->path, parent, new->name);
	if (lstat(new->path, new->stats) != 0)
	{
		if (!(is_repere(new->name) && !(is_hidden(new->name) || g_options & OPT_A)))
			ft_ls_error(0, new->name, 0);
		return (NULL);
	}
	if ((g_options & OPT_BR || g_sort & SORT_MOD) && queue && !(is_repere(new->name))
		&& (g_options & OPT_BR) && S_ISDIR(new->stats->st_mode)
			&&(!(is_hidden(new->name)) || (g_options & OPT_A)))
	{
			*recursive = 1;
			add_to_queue(queue, new->path);
	}
	return (new);
}

t_entry			*get_dir(char *path, t_list **queue, int *print_parent)
{
	t_entry		*start;
	t_dir		*current;
	DIR			*dir;
	
	start = NULL;
	if (*print_parent == 1)
		ft_printf("%s:\n", path);
	if (!(dir = opendir(path)))
	{
		// if (g_options & OPT_MULT || (g_options & OPT_BR && *queue))
		// 	ft_printf("%s:\n", path);
		ft_ls_error(0, ((ft_strrchr(path, '/') + 1) ?
			(ft_strrchr(path, '/') + 1) : path), 0);
		if ((g_options & OPT_BR || g_options & OPT_MULT) && *queue)
			ft_printf("\n");
		return (NULL);
	}
	while ((current = readdir(dir)) != NULL)
		ft_insert(&start, get_contents(path, queue, current->d_name, print_parent));
	closedir(dir);
	return (start);
}

int				ft_ls(t_list **queue)
{
	t_entry			*folder;
	t_list			*temp;
	t_list			*free_queue;
	int				print_parent;

	temp = *queue;
	folder = NULL;
	print_parent = g_options & OPT_MULT ? 1 : 0;
	while (temp)
	{
		if ((folder = get_dir((char *)temp->content, &(temp->next), &print_parent)))
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
