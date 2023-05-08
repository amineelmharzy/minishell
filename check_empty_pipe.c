/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:29:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/06 10:30:10 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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