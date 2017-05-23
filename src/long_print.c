/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:53:52 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/23 20:25:08 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern unsigned char g_options;
extern unsigned char g_sort;

static char		file_type(t_stat *stats)
{
	if (S_ISREG(stats->st_mode))
		return ('-');
	else if (S_ISDIR(stats->st_mode))
		return ('d');
	else if (S_ISLNK(stats->st_mode))
		return ('l');
	else if (S_ISBLK(stats->st_mode))
		return ('b');
	else if (S_ISFIFO(stats->st_mode))
		return ('p');
	else if (S_ISCHR(stats->st_mode))
		return ('c');
	else if (S_ISSOCK(stats->st_mode))
		return ('s');
	return (0);
}

static void		print_permissions(t_stat *stats)
{
	char	*ret;

	if (!stats)
		return ;
	if (!(ret = ft_strnew(12)))
		ft_ls_error(1, 0, 0);
	ret[0] = file_type(stats);
	ret[1] = ((stats->st_mode & S_IRUSR) ? 'r' : '-');
	ret[2] = ((stats->st_mode & S_IWUSR) ? 'w' : '-');
	ret[3] = ((stats->st_mode & S_IXUSR) ? 'x' : '-');
	if (stats->st_mode & S_ISUID)
		ret[3] = (ret[3] == 'x' ? 's' : 'S');
	ret[4] = ((stats->st_mode & S_IRGRP) ? 'r' : '-');
	ret[5] = ((stats->st_mode & S_IWGRP) ? 'w' : '-');
	ret[6] = ((stats->st_mode & S_IXGRP) ? 'x' : '-');
	if (stats->st_mode & S_ISGID)
		ret[6] = (ret[6] == 'x' ? 's' : 'S');
	ret[7] = ((stats->st_mode & S_IROTH) ? 'r' : '-');
	ret[8] = ((stats->st_mode & S_IWOTH) ? 'w' : '-');
	ret[9] = ((stats->st_mode & S_IXOTH) ? 'x' : '-');
	if (stats->st_mode & S_ISVTX)
		ret[9] = (ret[9] == 'x' ? 't' : 'T');
	ret[10] = '\0';
	ft_printf("%s", ret);
	free(ret);
}

static char		*get_time(t_entry *temp)
{
	char	*timestamp;

	if (g_sort & SORT_ACC)
		timestamp = ctime(&(temp->stats->st_atime));
	else if (g_sort & SORT_SC)
		timestamp = ctime(&(temp->stats->st_ctime));
	else
		timestamp = ctime(&(temp->stats->st_mtime));
	return (timestamp);
}

static void		print_name(t_entry *temp)
{
	if (S_ISLNK(temp->stats->st_mode) && temp->target)
		ft_printf("%s -> ", temp->target);
	ft_printf("%s\n", temp->name);
}

void			long_print(t_entry *temp, t_max *max)
{
	char	*timestamp;
	char	attr;

	timestamp = get_time(temp);
	print_permissions(temp->stats);
	attr = has_attr(temp);
	ft_printf("%c%*d %-*s  %-*s  ", attr, max->links + 1,
		temp->stats->st_nlink, max->uid, temp->usr->pw_name, max->gid,
		temp->grp->gr_name);
	if (is_device(temp->stats))
		ft_printf("%*d, %*d ", max->major, MAJOR(temp->stats->st_rdev),
			max->minor, MINOR(temp->stats->st_rdev));
	else
		ft_printf("%*lld ", max->size, temp->stats->st_size);
	if (timestamp)
		(recent(temp->stats)) ? ft_printf("%.12s ", timestamp + 4) :
			ft_printf("%.7s %4s ", timestamp + 4, ft_strtrim(timestamp + 20));
	print_name(temp);
	if (g_options & OPT_AT && attr == '@')
		print_attr(temp);
	if (g_options & OPT_E && get_acl(temp) && S_ISDIR(temp->stats->st_mode))
		print_acl(temp);
}
