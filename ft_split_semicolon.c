/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/31 12:04:09 by ael-mhar         ###   ########.fr       */
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

	if (!command)
		return (0);
	i = 0;
	j = 0;
	end = 0;
	start = 0;
	cmd = 0;
	while (command[i] != 0)
	{
		while (command[i] && command[i + 1] && command[i] == '\\' && command[i + 1] == ';')
			i += 2;
		if (command[i] && (command[i] == '\"' || command[i] == '\''))
		{
			start = command[i];
			i++;
			while (command[i] != 0 && command[i] != start)
				i++;
			if (command[i] && command[i] == start)
				end = 0;
			else
			{
				end = 1;
				i++;
			}
		}
		if (command[i] && command[i] == ';')
		{
			cmd = ft_calloc(i + 1, 1);
			j = 0;
			while (command[j] && j < i)
			{
				cmd[j] = command[j];
				j++;
			}
			cmd[j] = 0;
			return (cmd);
		}
		else if (command[i] && command[i + 1] == 0)
		{
			cmd = ft_calloc(ft_strlen(command) + 1, 1);
			j = 0;
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
	int		len;

	if (!str)
		return (NULL);
	array = ft_calloc(sizeof(char *) * (count_commands(str) + 1) + 1, 1);
	if (!array)
		return (NULL);
	i = 0;
	len = count_commands(str) + 1;
	while (i < len)
	{
		temp = get_command(str);
		array[i] = temp;
		str += ft_strlen(array[i]) + 1;
		i++;
	}
	array[i] = 0;
	return (array);
}

/*
int	main()
{
	char *cmd;
	while (1)
	{
		cmd = readline(" >> ");
		char	**s = ft_split_semicolon(cmd);
		int	i;

		i = 0;
		while (s[i] != 0)
		{
			printf("%s\n", s[i]);
			i++;
		}
	while(1);
	}
	return (0);
}
*/
