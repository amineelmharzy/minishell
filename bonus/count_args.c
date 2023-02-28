/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:25:17 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 21:26:21 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_counter2(char *str, int *i, int *count)
{
	if (str[*i] && str[*i] == ' ')
	{
		(*count)++;
		while (str[*i] != 0 && str[*i] == ' ')
			(*i)++;
		if (str[*i] == 0)
			(*count)--;
	}
	if (str[*i] && str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
}

int	count_args(char *command)
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
		ft_counter2(command, &i, &count);
	}
	return (count);
}
