/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:54:27 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/25 19:12:30 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_afiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	if (shell->afiles)
	{
		while (shell->afiles[i] != 0)
		{
			fd = open(shell->afiles[i], O_CREAT, 0644);
			close(fd);
			if (access(shell->afiles[i], F_OK | W_OK) == -1)
			{
				print_error(shell, shell->afiles[i], strerror(errno), 1);
				return (0);
			}
			if (!shell->afiles[i + 1] && shell->ofile == 2)
				shell->outfile = shell->afiles[i];
			i++;
		}
	}
	return (1);
}

int	init_outfiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	if (shell->outfiles)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
		while (shell->outfiles[i] != 0)
		{
			fd = open(shell->outfiles[i], O_CREAT | O_TRUNC, 0644);
			close(fd);
			if (access(shell->outfiles[i], F_OK | W_OK) == -1)
			{
				print_error(shell, shell->outfiles[i], strerror(errno), 1);
				return (0);
			}
			if (!shell->outfiles[i + 1] && shell->ofile == 1)
				shell->outfile = shell->outfiles[i];
			i++;
		}
	}
	if (!init_afiles(shell))
		return (0);
	return (1);
}
