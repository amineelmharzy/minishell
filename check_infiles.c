/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:25:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 18:05:07 by ael-mhar         ###   ########.fr       */
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
				shell->exit_status = 1;
				print_error(shell, shell->infiles[i], strerror(errno));
				return (0);
			}
		}
		else
		{
			shell->exit_status = 1;
			print_error(shell, shell->infiles[i], strerror(errno));
			return (0);
		}
		i++;
	}
	return (1);
}
