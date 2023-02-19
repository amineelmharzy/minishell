/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_equal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/17 15:21:47 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_equals(char *str)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	count = 0;
	start = 0;
	while (str[i] != 0)
	{
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			start = str[i];
			i++;
			while (str[i] != 0 && str[i] != start)
				i++;
			i++;
		}
		if (str[i] == '|')
		{
			i++;
			while (str[i] != 0 && str[i] != '\'' && str[i] != '\"' && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '|')
				return (-1);
			while (str[i] != 0 && str[i] != '|' && str[i] != '\"' && str[i] != '\'')
				i++;
			count++;
		}
		if (str[i] && str[i] != '|' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	return (count);
}

char	**ft_split_with_equal(char *command)
{
	int		i;
	int		j;
	int		start;
	char	*cmd;
	char	**array;

	if (!command)
		return (0);
	i = 0;
	j = 0;
	start = 0;
	cmd = ft_calloc(1, 1);
	array = ft_calloc(count_equals(command) + 2, sizeof(char *));
	if (!array)
		return (0);
	while (command[i] != 0)
	{
		while (command[i] && (command[i] == '\"' || command[i] == '\''))
		{
			start = command[i];
			cmd = ft_joinchar(cmd, command[i++]);
			while (command[i] != 0 && command[i] != start)
				cmd = ft_joinchar(cmd, command[i++]);
			cmd = ft_joinchar(cmd, command[i++]);
		}
		if (command[i] == '|')
		{
			i++;
			while (command[i] != 0 && command[i] != '\'' && command[i] != '\"' && command[i] == ' ')
				cmd = ft_joinchar(cmd, command[i++]);
			while (command[i] != 0 && command[i] != '|' && command[i] != '\"' && command[i] != '\'')
				cmd = ft_joinchar(cmd, command[i++]);
		}
		while (command[i] && command[i] != '|' && command[i] != '\'' && command[i] != '\"')
			cmd = ft_joinchar(cmd, command[i++]);
		if (command[i] != '\'' && command[i] != '\"')
		{
			array[j++] = cmd;
			cmd = 0;
			cmd = ft_calloc(1, 1);
		}
	}
	array[j] = 0;
	free(cmd);
	free(command);
	return (array);
}
