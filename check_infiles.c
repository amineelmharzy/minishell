/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:25:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/16 08:53:18 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infiles(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->infiles)
		return (1);
	while (shell->infiles[i] != 0)
	{
		if (access(shell->infiles[i], F_OK) != -1)
		{
			if (access(shell->infiles[i], R_OK) == -1)
			{
				shell->exit_status = 126;
				perror("Minishell ");
			}
		}
		else
		{
			shell->exit_status = 127;
			perror("Minishell ");
		}
		i++;
	}
	return (1);
}
