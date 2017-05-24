/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 16:25:44 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/24 21:05:14 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>

# define OPT_L		0b00000001
# define OPT_BR		0b00000010
# define OPT_A		0b00000100
# define OPT_E		0b00001000
# define OPT_BA		0b00010000
# define OPT_MULT	0b00100000
# define OPT_ONE	0b01000000
# define OPT_AT		0b10000000

# define SORT_REV	0b00000001
# define SORT_MOD	0b00000010
# define SORT_ACC	0b00000100
# define SORT_SC	0b00001000
# define SORT_SIZE	0b00010000
# define SORT_NONE	0b00100000

# define FT_LS_OPTIONS "1lRaAe@rtucSf"

# define MINOR(x) ((x) & 0xffffff)
# define MAJOR(x) (((x) >> 24) & 0xff)

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct			s_entry
{
	char				*path;
	char				*name;
	t_stat				*stats;
	struct passwd		*usr;
	struct group		*grp;
	struct s_entry		*next;
}						t_entry;

typedef struct			s_max
{
	int					has_contents;
	blkcnt_t			total;
	int					links;
	int					uid;
	int					gid;
	int					size;
	int					path;
	int					major;
	int					minor;
}						t_max;

int						ft_ls(t_list **queue);
t_entry					*get_contents(char *parent, t_list **queue,
	char *current, int *recursive);

void					add_to_queue(t_list **queue, char *path);
void					parse(int ac, char **av, t_list **queue);
void					get_options(int ac, char **av, int *i);

int						ft_ls_error(int quit, const char *name, int arnaud);
int						is_repere(char *path);
int						is_hidden(char *path);
char					*get_full_path(char *active, char *parent, char *file);
int						ft_strrcmp(const char *s1, const char *s2);
int						ft_numlen(long long nbr);

void					ft_ls_print(t_entry **start, int next, int folder);
void					long_print(t_entry *temp, t_max *max);
void					get_max(t_entry *start, t_max *max);

int						is_device(t_stat *stats);
void					print_attr(t_entry *temp);
void					print_acl(t_entry *temp);
int						get_terminal_width(void);
char					has_attr(t_entry *temp);
acl_t					get_acl(t_entry *temp);
int						recent(t_stat *stats);

t_entry					*new_entry(void);
void					ft_insert(t_entry **start, t_entry *new);
void					entry_addby(t_entry **alst, t_entry *new, \
	int(*cmp)(t_entry *, t_entry *), int rev);
void					entry_addafter(t_entry *lst, t_entry *new);
t_entry					*new_entry(void);
void					free_list(t_entry **start);

int						compare_path(t_entry *t1, t_entry *t2);
int						compare_time(t_entry *t1, t_entry *t2);
int						compare_size(t_entry *t1, t_entry *t2);
int						none(t_entry *t1, t_entry *t2);

#endif
