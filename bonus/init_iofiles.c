/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_iofiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:37:05 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/26 19:10:51 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_iofiles(t_shell *shell)
{
	if (!implement_redirection(shell))
		return (0);
	if (shell->herdocs)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
		shell->herdoc_output = herdoc(shell);
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
