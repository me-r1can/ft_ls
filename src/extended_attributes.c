/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:58:57 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/20 15:49:05 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

char		has_attr(t_entry *temp)
{
	char	ret;

	ret = ' ';
	if (get_acl(temp))
		ret = '+';
	if (listxattr(temp->path, 0, 0, 0) > 0)
		ret = '@';
	return (ret);
}

void		print_attr(t_entry *temp)
{
	char		*key;
	ssize_t		key_len;
	char		*val;
	ssize_t		val_len;
	ssize_t		buff_len;

	buff_len = listxattr(temp->path, NULL, 0, 0);
	if (!(key = ft_strnew(buff_len)))
		ft_ls_error(1, 0, 0);
	buff_len = listxattr(temp->path, key, buff_len, 0);
	while (buff_len > 0)
	{
		if ((val_len = getxattr(temp->path, key, NULL, 0, 0, 0)) == -1)
			return ;
		val = ft_strnew(val_len);
		val_len = getxattr(temp->path, key, val, val_len, 0, 0);
		val[val_len] = '\0';
		if (val_len > 0)
			ft_printf("\t%s\t  %ld\n", key, val_len);
		key_len = ft_strlen(key) + 1;
		buff_len -= key_len;
		key += key_len;
		free(val);
	}
}

acl_t		get_acl(t_entry *temp)
{
	acl_t	acl;

	if (!(acl = acl_init(1)))
		return (NULL);
	acl = acl_get_file((char *)temp->path, ACL_TYPE_EXTENDED);
	return (acl);
}

char		*read_acl(acl_t acl)
{
	char	*buffer;
	ssize_t	buff_len;

	acl_to_text(acl, &buff_len);
	if (buff_len <= 0)
		return (NULL);
	if (!(buffer = ft_strnew(buff_len)))
		ft_ls_error(1, 0, 0);
	buffer = acl_to_text(acl, 0);
	return (buffer);
}

void		print_acl(t_entry *temp)
{
	acl_t	acl;
	char	*buffer;
	char	**list;
	int		i;

	i = 0;
	if ((acl = get_acl(temp)) == NULL)
		return ;
	if (!(buffer = read_acl(acl)))
		return ;
	list = ft_strsplit(ft_strchr(buffer, '\n') + 1, ':');
	if (list[i])
		ft_printf(" 0: %s:", list[i++]);
	while (list[i] != NULL)
	{
		if ((i < 4 && i % 2 == 0) || i >= 4)
			ft_printf(" %s", list[i]);
		free(list[i]);
		i++;
	}
	free(list);
	free(buffer);
	acl_free(acl);
}
