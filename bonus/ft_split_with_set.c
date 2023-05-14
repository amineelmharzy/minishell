/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/14 13:48:02 by ael-mhar         ###   ########.fr       */
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
			&& str[*i] != '\"' && str[*i] != '\'' && str[*i] != '(')
			(*i)++;
		(*count)++;
	}
	else
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
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == set[0])
		return (-1);
	while (str[i] != 0)
	{
		while (str[i] && (str[i] == '\"' || str[i] == '\'' || str[i] == '('))
		{
			start = str[i++];
			if (start == '(')
				start = ')';
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
		if (command[*i] == '(')
			start = ')';
		else
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		while (command[*i] != 0 && !check_end(command, *i, start))
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		if (command[*i] != 0)
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

char	**ft_split_with_set(t_shell *shell, char *command, char *set)
{
	int		i;
	int		j;
	char	*cmd;
	char	**array;

	init_vars(&i, &j, &cmd);
	if (count_set(command, set) == -1)
		return (free(cmd), _print_error(shell, E_ANDO, 2), NULL);
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
