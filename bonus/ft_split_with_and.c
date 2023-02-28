/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_and.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/28 19:05:51 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_counter(char *str, char *set, int *i, int *count)
{
	int	j;

	j = 0;
	if (str[*i] && str[*i] == set[0] && str[*i + 1] && str[*i + 1] == set[0])
	{
		(*i) += 2;
		while (str[*i] != 0 && str[*i] != '\'' && str[*i] != '\"'
			&& str[*i] == ' ')
			(*i)++;
		if (!str[*i] || str[*i] == set[0])
			return (-1);
		while (str[*i] != 0 && str[*i] != set[0] && str[*i] != '\"'
			&& str[*i] != '\'')
			(*i)++;
		(*count)++;
	}
	if (str[*i] == set[0] && str[*i + 1] != set[0])
		return (-1);
	if (str[*i] && str[*i] != set[0] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	return (0);
}

int	count_set(char *str, char *set)
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

void	get_command(char **cmd, char *command, char *set, int *i)
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
	while (command[*i] != 0 && command[*i] != set[0] && command[*i] != '\'' && command[*i] != '\"')
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
}

void	init_vars(int *i, int *j, char **cmd)
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
		return (0);
	while (command[i] != 0)
	{
		get_command(&cmd, command,set, &i);
		if (!command[i] || (command[i] == set[0] && command[i + 1] && command[i + 1] == set[1]))
		{
			if (command[i] == set[0])
				i += 2;
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
/*
int	main(int ac, char **av)
{
	char *s = readline("> ");
	char **array;
	int	i;
	array = ft_split_with_set(s, "&&");
	i = 0;
	if (array)
	{
		while (array[i] != 0)
			printf("%s\n", array[i++]);
	}
}
*/
