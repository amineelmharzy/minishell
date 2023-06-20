/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by yaidriss          #+#    #+#             */
/*   Updated: 2023/06/17 13:08:20 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_arg(char **cmd, char *command, int *i, int option)
{
	int	start;

	start = 0;
	while (command[*i] && (command[*i] == '\"' || command[*i] == '\''))
	{
		start = command[*i];
		if (option == -1)
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		else
			(*i)++;
		while (command[*i] != 0 && command[*i] != start)
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		if (option == -1 && command[*i])
			*cmd = ft_joinchar(*cmd, command[(*i)++]);
		else if (command[*i] != 0 && command[*i] == start)
			(*i)++;
	}
}

void	parse_arg_after(char **cmd, char *command, int *i)
{
	if (command[*i] && command[*i] != '\"' && command[*i] != '\''
		&& command[*i] != ' ')
		*cmd = ft_joinchar(*cmd, command[(*i)++]);
}

void	init_variables(char **cmd, char *command, int *i)
{
	*i = 0;
	*cmd = ft_calloc(1, 1);
	while (command[*i] != 0 && command[*i] == ' ')
		(*i)++;
}

void	ft_run_split(char ***array, char *command, int *j, int option)
{
	int		i;
	char	*cmd;

	init_variables(&cmd, command, &i);
	while (command[i] != 0)
	{
		parse_arg(&cmd, command, &i, option);
		if (!command[i] || command[i] == ' ')
		{
			while (command[i] != 0 && command[i] == ' ')
				i++;
			(*array)[(*j)++] = cmd;
			cmd = 0;
			cmd = ft_calloc(1, 1);
		}
		parse_arg_after(&cmd, command, &i);
		if (!command[i] && cmd[0])
		{
			(*array)[(*j)++] = cmd;
			cmd = ft_calloc(1, 1);
		}
	}
	(*array)[*j] = 0;
	free(cmd);
}

char	**ft_split_with_space(char *command, int option)
{
	char	**array;
	int		j;

	if (!command || !command[0])
		return (NULL);
	array = ft_calloc(count_args(command) + 2, sizeof(char *));
	if (!array)
		return (NULL);
	j = 0;
	ft_run_split(&array, command, &j, option);
	free(command);
	return (array);
}
