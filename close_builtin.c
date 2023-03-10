/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:27:21 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/06 08:27:30 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_exit_(t_shell *shell)
{
	shell->exit_status = 0;
}

void	close_builtin(t_shell *shell, int option)
{
	if (option == 0 && shell->is_builtin)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
	}
	else if (option == 1 && !shell->is_pipe)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
	}
}
