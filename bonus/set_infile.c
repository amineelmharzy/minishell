/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:13:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/15 18:19:13 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_infile(t_shell *shell)
{
	int	i;

	i = ft_strlen(shell->command) - 1;
	while (i >= 0)
	{
		if (shell->command[i] == '<' && i > 0 && shell->command[i - 1] == '<')
		{
			shell->ifile = 2;
			break ;
		}
		if (shell->command[i] == '<')
		{
			shell->ifile = 1;
			break ;
		}
		i--;
	}
}
