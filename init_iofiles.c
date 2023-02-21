/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_iofiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:37:05 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 11:49:02 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_iofiles(t_shell *shell)
{
	if (!implement_redirection(shell))
		return (0);
	if (!check_infiles(shell))
		return (0);
	if (shell->herdocs)
		shell->herdoc_output = herdoc(shell);
	if (shell->outfiles || shell->afiles)
	{
		if (!init_outfiles(shell))
			return (0);
	}
	return (1);
}
