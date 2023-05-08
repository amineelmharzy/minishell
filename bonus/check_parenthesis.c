/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:49:23 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/08 19:02:43 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *str, int *i)
{
	int	start;

	while (str[*i] && (str[*i] == '\"' || str[*i] == '\''))
	{
		start = str[(*i)++];
		while (str[*i] && str[*i] != start)
			(*i)++;
		(*i)++;
	}
}

int	check_nearp(char *str, int i)
{
	while (str[i] != 0 && str[i] != '(' && str[i] != ')')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (!str[i] || str[i] == '(' || str[i] == ')')
				return (-1);
			while (str[i] && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '<' && str[i] != '>'
				&& str[i] != '(' && str[i] != ')')
				i++;
		}
		else if (str[i] == '|' || str[i] == '&')
			return (0);
		else if (str[i] != 0 && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '(' && str[i] != ')')
			return (-1);
		else
			i++;
	}
	return (0);
}

int	check_otherp(char *str, int count_o, int count_c, int i)
{
	if (count_o != count_c)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '|')
	{
		i++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (!str[i])
			return (1);
	}
	if (str[i] == '(' || str[i] == ')')
		return (1);
	return (0);
}

int	check_end(char *str, int i, int start)
{
	int	count_o;
	int	count_c;
	int	j;

	count_o = 0;
	count_c = 0;
	j = -1;
	if (start != ')')
	{
		if (str[i] == start)
			return (1);
		return (0);
	}
	while (++j < i)
	{
		if (str[j] == '(')
			count_o++;
		if (str[j] == ')')
		{
			count_c++;
			if (count_o == count_c)
				return (1);
		}
	}
	return (0);
}

int	check_parenthesis(char *str)
{
	int	i;
	int	count_o;
	int	count_c;

	i = 0;
	count_o = 0;
	count_c = 0;
	while (str[i] != 0)
	{
		skip_quotes(str, &i);
		if (count_c > count_o)
			return (-1);
		if (str[i] == '(')
			count_o++;
		else if (str[i] == ')')
		{
			if (++count_c && (check_nearp(str, i + 1) == -1
					|| check_otherp(str, count_c, count_o, i + 1)))
				return (-1);
		}
		i++;
	}
	if (count_o != count_c)
		return (-1);
	return (0);
}
