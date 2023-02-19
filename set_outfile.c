/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_outfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:29:54 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 15:30:02 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_outfile(t_shell *shell)
{
	int	i;

	i = ft_strlen(shell->command) - 1;
	while (i >= 0)
	{
		if (shell->command[i] == '>' && i > 0 && shell->command[i - 1] == '>')
		{
			shell->ofile = 2;
			break ;
		}
		if (shell->command[i] == '>')
		{
			shell->ofile = 1;
			break ;
		}
		i--;
	}
}
