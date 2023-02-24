/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_iofiles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:16:02 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/22 15:20:48 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_iofiles(char *command, char *set)
{
	int	i;

	i = 0;
	while (command[i] != 0)
	{
		if (command[i] && ft_strlen(&command[i]) >= ft_strlen(set)
			&& !ft_strncmp(&command[i], set, ft_strlen(set)))
		{
			i += ft_strlen(set);
			while (command[i] != 0 && command[i] == ' ')
				i++;
			if (command[i] && (command[i] == '\"' || command[i] == '\''))
			{
				i++;
				if (command[i] && (command[i] == '\"' || command[i] == '\''))
					return (1);
			}
		}
		i++;
	}
	return (0);
}
