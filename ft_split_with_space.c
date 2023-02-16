/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/15 15:51:49 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char *command)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	start = 0;
	count = 0;
	while (command[i] != 0 && command[i] == ' ')
		i++;
	while (command[i] != 0)
	{
		while (command[i] && (command[i] == '\"' || command[i] == '\''))
		{
			start = command[i];
			i++;
			while (command[i] != 0 && command[i] != start)
				i++;
			if (command[i] == start)
				i++;
		}
		if (command[i] && command[i] == ' ')
		{
			count++;
			while (command[i] != 0 && command[i] == ' ')
				i++;
			if (command[i] == 0)
				count--;
		}
		if (command[i] && command[i] != '\"' && command[i] != '\'')
			i++;
	}
	return (count);
}

char	**ft_split_with_space(char *command)
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
	array = ft_calloc(count_commands(command) + 2, sizeof(char *));
	if (!array)
		return (0);
	while (command[i] != 0 && command[i] == ' ')
		i++;
	while (command[i] != 0)
	{
		while (command[i] && (command[i] == '\"' || command[i] == '\''))
		{
			start = command[i];
			i++;
			while (command[i] != 0 && command[i] != start)
				cmd = ft_joinchar(cmd, command[i++]);
			if (command[i] && command[i] == start)
				i++;
		}
		while (command[i] != 0 && command[i] != ' ')
			cmd = ft_joinchar(cmd, command[i++]);
		if (!command[i] || command[i] == ' ')
		{
			while (command[i] != 0 && command[i] == ' ')
				i++;
			array[j++] = cmd;
			cmd = 0;
			cmd = ft_calloc(1, 1);
		}
		if (command[i] && command[i] != '\"' && command[i] != '\'' && command[i] != ' ')
			cmd = ft_joinchar(cmd, command[i++]);
		if (!command[i] && cmd[0])
		{
			array[j++] = cmd;
			cmd = ft_calloc(1, 1);
		}
	}
	array[j] = 0;
	free(cmd);
	free(command);
	return (array);
}

/*
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
int	main(int ac, char **av)
{
	char	*s;
	char	**array;
	int	i;
	i = 0;
   	s = readline(">> ");
	array = ft_split_with_space(s);
	while (array[i])
	{
		printf("%s\n",array[i]);
		i++;
	}
	while (array[i] != 0)
	{
		printf("%s\n", array[i]);
		i++;
	}
	while (s)
	{
		i = 0;
   		s = readline(">> ");
		array = ft_split_with_space(s);
		while (array[i] != 0)
		{
			printf("%s\n", array[i]);
			i++;
		}
	}
	return (0);
}
*/
