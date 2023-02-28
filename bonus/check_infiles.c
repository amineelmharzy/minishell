/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:25:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/26 16:40:13 by ael-mhar         ###   ########.fr       */
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
		if (shell->infiles[i][0] == '$')
		{
			print_error(shell, shell->infiles[i], E_AMBR, 1);
			return (0);
		}
		if (access(shell->infiles[i], F_OK) != -1)
		{
			if (access(shell->infiles[i], R_OK) == -1)
			{
				print_error(shell, shell->infiles[i], strerror(errno), 1);
				return (0);
			}
		}
		else
		{
			print_error(shell, shell->infiles[i], strerror(errno), 1);
			return (0);
		}
		i++;
	}
	close(0);
	dup2(shell->stdin_fd, 0);
	return (1);
}
