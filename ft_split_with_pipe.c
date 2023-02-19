/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 14:36:59 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_counter(char *str, int *i, int *count)
{
	if (str[*i] == '|')
	{
		(*i)++;
		while (str[*i] != 0 && str[*i] != '\'' && str[*i] != '\"'
			&& str[*i] == ' ')
			(*i)++;
		if (!str[*i] || str[*i] == '|')
			return (-1);
		while (str[*i] != 0 && str[*i] != '|' && str[*i] != '\"'
			&& str[*i] != '\'')
			(*i)++;
		(*count)++;
	}
	if (str[*i] && str[*i] != '|' && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	return (0);
}

int	count_pipes(char *str)
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
		if (ft_counter(str, &i, &count) == -1)
			return (-1);
	}
	return (count);
}

void	expand_with(char **cmd, char *str, int *i)
{
	int	start;

	start = str[*i];
	*cmd = ft_joinchar(*cmd, str[(*i)++]);
	while (str[*i] != 0 && str[*i] != start)
		*cmd = ft_joinchar(*cmd, str[(*i)++]);
	*cmd = ft_joinchar(*cmd, str[(*i)++]);
}

void	expand_after(char **array, char **cmd, char *str, int *i)
{
	if (str[*i] == '|')
	{
		(*i)++;
		while ((str)[*i] != 0 && (str)[*i] != '\'' && (str)[*i] != '\"'
			&& (str)[*i] != ' ')
			*cmd = ft_joinchar(*cmd, (str)[(*i)++]);
		while ((str)[*i] != 0 && (str)[*i] != '|' && (str)[*i] != '\"'
			&& (str)[*i] != '\'')
			*cmd = ft_joinchar(*cmd, (str)[(*i)++]);
	}
	while (str[*i] && str[*i] != '|' && str[*i] != '\'' && str[*i] != '\"')
		*cmd = ft_joinchar(*cmd, str[(*i)++]);
	if (str[*i] != '\'' && str[*i] != '\"')
	{
		*array = *cmd;
		*cmd = 0;
		*cmd = ft_calloc(1, 1);
	}
}

char	**ft_split_with_pipe(char *command)
{
	int		i;
	int		j;
	char	*cmd;
	char	**array;

	if (!command)
		return (0);
	i = 0;
	j = 0;
	cmd = ft_calloc(1, 1);
	array = ft_calloc(count_pipes(command) + 2, sizeof(char *));
	if (!array)
		return (0);
	while (command[i] != 0)
	{
		if (command[i] && (command[i] == '\"' || command[i] == '\''))
			expand_with(&cmd, command, &i);
		expand_after(&array[j++], &cmd, command, &i);
	}
	array[j] = 0;
	free(cmd);
	free(command);
	return (array);
}
