/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/27 16:43:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char *command)
{
	int	i;
	int	end;
	int	start;
	int	count;

	i = 0;
	end = 0;
	start = 0;
	count = 0;
	while (command[i] != 0)
	{
		while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
			i++;
		if (command[i] == '\"' || command[i] == '\'')
		{
			start = command[i];
			i++;
			while (command[i] != 0 && command[i] != start)
				i++;
			if (command[i] == start)
				end = 0;
			else
			{
				end = 1;
				i++;
			}
		}
		if (command[i] == ';')
			count++;
		i++;
	}
	return (count);
}

char	*get_command(char *command)
{
	int		i;
	int		j;
	int		end;
	int		start;
	char	*cmd;

	i = 0;
	j = 0;
	end = 0;
	start = 0;
	while (command[i] != 0)
	{
		while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'
				|| command[i] == '\n'))
			i++;
		while (command[i] == '\\' && command[i + 1] == ';')
			i += 2;
		if (command[i] == '\"' || command[i] == '\'')
		{
			start = command[i];
			i++;
			while (command[i] != 0 && command[i] != start)
				i++;
			if (command[i] == start)
				end = 0;
			else
			{
				end = 1;
				i++;
			}
		}
		if (command[i] == ';')
		{
			cmd = malloc(i + 1);
			while (j < i)
			{
				cmd[j] = command[j];
				j++;
			}
			cmd[j] = 0;
			return (cmd);
		}
		else if (command[i + 1] == 0)
		{
			cmd = malloc(ft_strlen(command) + 1);
			while (command[j] != 0)
			{
				cmd[j] = command[j];
				j++;
			}
			cmd[j] = 0;
			return (cmd);
		}
		i++;
	}
	return (0);
}

char	**ft_split_semicolon(char *str)
{
	char	**array;
	char	*temp;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * (count_commands(str) + 1) + 1);
	temp = get_command(str);
	while (temp)
	{
		j = 0;
		array[i++] = temp;
		while (j <= ft_strlen(temp))
		{
			j++;
			str++;
		}
		temp = get_command(str);
	}
	array[i] = 0;
	return (array);
}
