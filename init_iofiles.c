/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_iofiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:37:05 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 19:01:14 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_herdoc(t_shell *shell)
{
	int	pid;
	int	status;

	if (pipe(shell->herdoc) == -1)
		return (_print_error(shell, strerror(errno), 1), 0);
	pid = fork();
	if (!pid)
		herdoc(shell);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(shell->herdoc[1]);
		_exit_status(shell, status);
		if (shell->exit_status)
			return (dup2(shell->stdin_fd, 0), 0);
	}
	else
		return (_print_error(shell, strerror(errno), 1), 0);
	return (1);
}

int	init_iofiles(t_shell *shell)
{
	int	pid;
	int	status;

	if (!implement_redirection(shell))
		return (0);
	if (shell->herdocs)
	{
		if (!init_herdoc(shell))
			return (0);
	}
	if (!check_infiles(shell))
		return (0);
	if (shell->outfiles || shell->afiles)
	{
		if (!init_outfiles(shell))
			return (0);
	}
	return (1);
}
