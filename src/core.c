/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:29:40 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 17:56:39 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

t_entry			*get_contents(char *parent, t_list **queue, char *current,
	int *recursive)
{
	t_entry		*new;

	if (!(new = new_entry()))
		ft_ls_error(1, 0, 0);
	new->name = ft_strdup(current);
	get_full_path(new->path, parent, new->name);
	if (lstat(new->path, new->stats) != 0)
	{
		if (!(is_repere(new->name)) && (!(is_hidden(new->name))
		|| g_options & OPT_A))
			ft_ls_error(0, new->name, 0);
		return (NULL);
	}
	if (g_options & OPT_BR && S_ISDIR(new->stats->st_mode)
		&& !(is_repere(new->name)) && queue
		&& (!(is_hidden(new->name)) || (g_options & OPT_A)))
	{
		*recursive = 1;
		add_to_queue(queue, new->path);
	}
	return (new);
}

void			print_newline(int *print_parent)
{
	if (*print_parent == 1)
		ft_printf("\n");
	else if (g_options & OPT_MULT)
		*print_parent = 1;
}

void			print_dir(char *path, int *print_parent)
{
	t_entry		*start;
	t_dir		*current;
	DIR			*dir;
	t_list		*local;

	start = NULL;
	local = NULL;
	print_newline(print_parent);
	if (*print_parent == 1)
		ft_printf("%s:\n", path);
	if (!(dir = opendir(path)))
	{
		ft_ls_error(0, ((ft_strrchr(path, '/') + 1) ?
			(ft_strrchr(path, '/') + 1) : path), 0);
		return ;
	}
	while ((current = readdir(dir)) != NULL)
		ft_insert(&start, get_contents(path, &local,
		current->d_name, print_parent));
	closedir(dir);
	ft_ls_print(&start, 1);
	free_list(&start);
	if (local)
		ft_ls(&local, *print_parent);
}

int				ft_ls(t_list **queue, int print_parent)
{
	t_entry			*folder;
	t_list			*temp;
	t_list			*free_queue;

	temp = *queue;
	folder = NULL;
	while (temp)
	{
		print_dir((char *)temp->content, &print_parent);
		free_queue = temp;
		temp = temp->next;
		free(free_queue->content);
		free(free_queue);
	}
	return (1);
}
