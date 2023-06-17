/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astric.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:36:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/05 17:04:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__lst_index(char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == c)
			break ;
		i--;
	}
	return (i);
}

int	__is_in_file(char *file, char *user_file, int _start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (user_file[i] != 0)
	{
		if (user_file[i] == '*')
		{
			while (user_file[i] && user_file[i] == '*')
				i++;
			if (!user_file[i])
				return (1);
			while (file[j] && j < __lst_index(file, user_file[i]))
				j++;
		}
		else if (user_file[i] != file[j])
			return (-1);
		while (user_file[i] && file[j] && user_file[i] == file[j]
			&& user_file[i++] != '*')
			j++;
		if (!user_file[i] && file[j])
			return (-1);
	}
	return (1);
}

void	__next_l(t_node *node, char *_file)
{
	t_node	*save;
	int		res;

	while (node)
	{
		if (node->index != -1)
		{
			res = __is_in_file(node->content, _file, node->index);
			node->index = res;
		}
		node = node->next;
	}
}

char	*get_matched(char *file_name, char *s, int i)
{
	t_node	*head;
	t_node	*tmp;
	char	*res;

	i = 0;
	res = 0;
	if (file_name[0] == '.')
		head = __astric_l(s, 1);
	else
		head = __astric_l(s, 0);
	res = ft_calloc(1, 1);
	__next_l(head, file_name);
	while (head)
	{
		if (head->index != -1)
			res = ft_joinstr(res, ft_joinchar(head->content, ' '));
		else
			free(head->content);
		tmp = head->next;
		free(head);
		head = tmp;
	}
	if (!res || !res[0])
		return (free(res), file_name);
	return (free(file_name), res);
}

char	*expand_astric(char **str)
{
	int		i;
	int		chk;
	char	*regex;

	i = -1;
	chk = 0;
	regex = ft_calloc(1, 1);
	while ((*str)[++i] != 0 && (*str)[i] != ' ' && (*str)[i] != '\''
		&& (*str)[i] != '\"')
	{
		if ((*str)[i] == '*')
			chk = 1;
		regex = ft_joinchar(regex, (*str)[i]);
	}
	if (chk)
	{
		*str += i;
		return (get_matched(regex, ".", 0));
	}
	free(regex);
	regex = ft_chardup((*str)[0]);
	(*str)++;
	return (regex);
}
