/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/09 18:21:32 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_counter(char *str, char *set, int *i, int *count)
{
	if (str[*i] && str[*i] == set[0] && str[*i + 1] && str[*i + 1] == set[1])
	{
		(*i) += 2;
		while (str[*i] != 0 && str[*i] != '\'' && str[*i] != '\"'
			&& str[*i] == ' ')
			(*i)++;
		if (!str[*i] || (str[*i] == set[0]))
			return (-1);
		while (str[*i] != 0 && !(str[*i] == set[0] && str[*i + 1] == set[1])
			&& str[*i] != '\"'
			&& str[*i] != '\'')
			(*i)++;
		(*count)++;
	}
	else
		(*i)++;
	return (0);
}

static int	count_set(char *str, char *set)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	count = 0;
	start = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == set[0])
		return (-1);
	while (str[i] != 0)
	{
		while (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			start = str[i];
			i++;
			while (str[i] != 0 && str[i] != start)
				i++;
			i++;
		}
		if (ft_counter(str, set, &i, &count) == -1)
			return (-1);
	}
	return (count);
}

static void	get_command(char **cmd, char *command, char *set, int *i)
{
	int	start;

	while (command[*i] && (command[*i] == '\"' || command[*i] == '\''
		|| command[*i] == '('))
	{
		start = command[*i];
		if (start == '(')
			start = ')';
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
		while (command[*i] != 0 && command[*i] != start)
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
	}
	while (command[*i] != 0
		&& !(command[*i] == set[0] && command[*i + 1] == set[1])
		&& command[*i] != '\'' && command[*i] != '\"' && command[*i] != '(')
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
}

static void	init_vars(int *i, int *j, char **cmd)
{
	*i = 0;
	*j = 0;
	*cmd = ft_calloc(1, 1);
}

char	**ft_split_with_set(char *command, char *set)
{
	int		i;
	int		j;
	char	*cmd;
	char	**array;

	init_vars(&i, &j, &cmd);
	if (count_set(command, set) == -1)
		return (NULL);
	array = ft_calloc(count_set(command, set) + 2, sizeof(char *));
	if (!array)
		return (NULL);
	while (command[i] != 0)
	{
		get_command(&cmd, command, set, &i);
		if (!command[i] || (command[i] == set[0]
				&& command[i + 1] && command[i + 1] == set[1]))
		{
			if (command[i] == set[0])
				i += 2;
			array[j++] = cmd;
			cmd = ft_calloc(1, 1);
		}
	}
	array[j] = 0;
	return (free(cmd), free(command), array);
}
/*
int	main(int ac, char **av)
{
	int	i;

	i = 0;
	char **s = ft_split_with_set(ft_strdup(av[1]), "||");
	while (s[i] != 0)
	{
		printf("%s\n", s[i++]);
	}
	return (0);
}
*/
