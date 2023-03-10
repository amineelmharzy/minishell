/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:25:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/06 08:43:43 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infile(t_shell *shell, char *infile)
{
	if (access(infile, F_OK) != -1)
	{
		if (access(infile, R_OK) == -1)
		{
			print_error(shell, infile, strerror(errno), 1);
			return (0);
		}
	}
	else
	{
		print_error(shell, infile, strerror(errno), 1);
		return (0);
	}
	return (1);
}

int	check_infiles(t_shell *shell)
{
	int	i;

	i = -1;
	if (!shell->infiles)
		return (1);
	while (shell->infiles[++i] != 0)
	{
		if (check_ambiguous_redirect(shell, shell->infiles[i],
				shell->infiles[i]))
			return (0);
		if (!check_infile(shell, shell->infiles[i]))
			return (0);
	}
	close(0);
	dup2(shell->stdin_fd, 0);
	return (1);
}
