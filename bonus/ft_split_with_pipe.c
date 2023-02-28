/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/26 20:03:26 by ael-mhar         ###   ########.fr       */
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

int	check_empty_pipe(char *str, int i)
{
	while (i >= 0)
	{
		if (str[i] != ' ' && str[i] != '>' && str[i] != '<')
			return (0);
		i--;
	}
	return (1);
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
		while (str[i] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
			i++;
		if (str[i] == '|' && check_empty_pipe(str, i - 1))
			return (-1);
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

void	get_command(char **cmd, char *command, int *i)
{
	int	start;

	while (command[*i] && (command[*i] == '\"' || command[*i] == '\''))
	{
		start = command[*i];
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
		while (command[*i] != 0 && command[*i] != start)
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
	}
	if (command[*i] && command[*i] != '\"' && command[*i] != '\''
		&& command[*i] != '|')
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
}

void	init_vars(int *i, int *j, char **cmd)
{
	*i = 0;
	*j = 0;
	*cmd = ft_calloc(1, 1);
}

char	**ft_split_with_pipe(char *command)
{
	int		i;
	int		j;
	char	*cmd;
	char	**array;

	init_vars(&i, &j, &cmd);
	array = ft_calloc(count_pipes(command) + 2, sizeof(char *));
	if (!array)
		return (0);
	while (command[i] != 0)
	{
		get_command(&cmd, command, &i);
		if (!command[i] || command[i] == '|')
		{
			if (command[i] == '|')
				i++;
			array[j++] = cmd;
			cmd = 0;
			cmd = ft_calloc(1, 1);
		}
	}
	free(cmd);
	free(command);
	return (array);
}
