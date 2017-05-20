/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddbystr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:18:36 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/20 16:27:45 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstaddbystr(t_list **alst, t_list *new,
	int (*cmp)(const char *, const char *))
{
	t_list		*current;
	t_list		*previous;

	current = *alst;
	previous = NULL;
	while ((current != NULL) && cmp((char *)new->content,
		(char *)current->content) >= 0)
	{
		previous = current;
		current = current->next;
	}
	if (previous != NULL)
		ft_lstaddafter(previous, new);
	else
		ft_lstaddfront(alst, new);
}
