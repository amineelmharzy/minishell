/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:42:16 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/16 17:09:01 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	_wtermsig(int status)
{
	return ((status) & 0x7f);
}

int	_wifexited(int status)
{
	return (_wtermsig(status) == 0);
}

int	_wifsignaled(int status)
{
	return (((signed char)(((status) & 0x7f) + 1) >> 1) > 0);
}

void	_exit_status(t_shell *shell, int status)
{
	int	signal_number;

	if (_wifexited(status))
	{
		shell->exit_status = _wexitstatus(status);
	}
	else if (_wifsignaled(status))
	{
		signal_number = _wtermsig(status);
		if (signal_number == SIGINT || signal_number == SIGQUIT)
		{
			shell->exit_status = 128 + signal_number;
			g_status = 0;
		}
	}
}
