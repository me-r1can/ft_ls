/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 23:20:31 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/24 21:06:31 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

static int	dir_exists(char *active, t_list **file_queue, t_list **error_queue)
{
	t_list	*new;
	DIR		*dir;

	errno = 0;
	dir = NULL;
	if (readlink(active, NULL, 0) != -1 && g_options & OPT_L)
		errno = 20;
	else if ((dir = opendir(active)) ||
		(errno != 2 && errno != 20 && errno != 13))
		return (1);
	if (!(new = ft_lstnew(active, ft_strlen(active) + 1)))
		ft_ls_error(1, 0, 0);
	if (errno == 20 || (errno == 2 && readlink(active, NULL, 0) != -1))
		ft_lstaddbystr(file_queue, new, ft_strcmp);
	else if (errno == 13)
		ft_ls_error(0, active, 0);
	else
		ft_lstaddbystr(error_queue, new, ft_strcmp);
	if (dir)
		closedir(dir);
	return (0);
}

static void	print_file_queue(t_list *file_queue, int next)
{
	t_entry		*start;
	t_list		*temp;
	t_list		*free_queue;

	if (file_queue == NULL)
		return ;
	start = NULL;
	temp = file_queue;
	while (temp)
	{
		ft_insert(&start, get_contents((((char *)(temp->content))[0] == '/')
			? "" : ".", NULL, (char *)temp->content, 0));
		free_queue = temp;
		temp = temp->next;
		free(free_queue->content);
		free(free_queue);
	}
	ft_ls_print(&start, 0, 0);
	free_list(&start);
	if ((g_options & OPT_BR || g_options & OPT_MULT) && next)
		ft_printf("\n");
}

static void	print_empties(t_list *error_queue)
{
	t_list		*temp;
	t_list		*free_queue;

	temp = error_queue;
	if (temp == NULL)
		return ;
	while (temp)
	{
		ft_ls_error(0, (char *)temp->content, 2);
		free_queue = temp;
		temp = temp->next;
		free(free_queue->content);
		free(free_queue);
	}
}

void		add_to_queue(t_list **queue, char *path)
{
	char		*active;
	t_list		*new;

	if (!((active = ft_strnew(PATH_MAX))))
		ft_ls_error(1, 0, 0);
	ft_strncpy(active, path, PATH_MAX);
	if (!(new = ft_lstnew(active, PATH_MAX + 1)))
		ft_ls_error(1, 0, 0);
	if (g_sort & SORT_REV)
		ft_lstaddbystr(queue, new, ft_strrcmp);
	else
		ft_lstaddbystr(queue, new, ft_strcmp);
	free(active);
}

void		parse(int ac, char **av, t_list **queue)
{
	char		*active;
	t_list		*file_queue;
	t_list		*error_queue;
	int			i;

	i = 1;
	file_queue = NULL;
	error_queue = NULL;
	get_options(ac, av, &i);
	if (!((active = ft_strnew(PATH_MAX))))
		ft_ls_error(1, 0, 0);
	if (i == ac)
		add_to_queue(queue, ".");
	else
	{
		while (i < ac)
		{
			if (dir_exists(av[i], &file_queue, &error_queue) == 1)
				add_to_queue(queue, av[i]);
			i++;
		}
		print_empties(error_queue);
		print_file_queue(file_queue, (*queue) ? 1 : 0);
	}
	free(active);
}
