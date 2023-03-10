/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astric_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:34:08 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/09 15:56:49 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstnew(char *content, int index)
{
	t_node	*l;

	l = (t_node *)malloc(sizeof(t_node));
	if (!l)
		return (NULL);
	l->content = content;
	l->index = index;
	l->next = NULL;
	return (l);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*res;

	res = *lst;
	if (*lst == NULL && new != NULL)
	{
		*lst = new;
		return ;
	}
	else if (lst == NULL || new == NULL)
	{
		return ;
	}
	while ((*lst)->next != NULL)
	{
		*lst = (*lst)->next;
	}
	(*lst)->next = new;
	*lst = res;
}

char	*__func_l(char *file_name)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	while (file_name[i] && file_name[i] == '*')
		i++;
	while (file_name[i] != 0)
	{
		while (file_name[i] && file_name[i] != '*')
			i++;
		if (file_name[i] == '*')
		{
			res = ft_joinchar(res, file_name[i]);
			while (file_name[i] && file_name[i] == '*')
				i++;
			while (file_name[i] && file_name[i] != '*')
				res = ft_joinchar(res, file_name[i++]);
		}
	}
	if (!res[0])
		return (free(res), NULL);
	return (res);
}

t_node	*__astric_l(char *path, int is_hidden)
{
	t_node			*head;
	t_node			*new_node;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	head = 0;
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' || is_hidden)
		{
			if (ft_strchr(path, '/'))
				new_node = ft_lstnew(ft_strjoin(path, entry->d_name), 0);
			else
				new_node = ft_lstnew(ft_strdup(entry->d_name), 0);
			ft_lstadd_back(&head, new_node);
		}
		entry = readdir(dir);
	}
	return (head);
}

char	*ft_chardup(char c)
{
	char	*s;

	s = ft_calloc(2, 1);
	s[0] = c;
	s[1] = 0;
	return (s);
}
