/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:49:23 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/11 16:50:31 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *str, int *i)
{
	int	start;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		start = str[(*i)++];
		while (str[*i] && str[*i] != start)
			(*i)++;
		(*i)++;
	}
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
			count_c++;
		if (str[i])
			i++;
	}
	if (count_o != count_c)
		return (-1);
	return (0);
}
