/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/07 17:27:47 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command(t_shell *shell, int i)
{
	shell->parsed_command = 0;
	/*
	if (g_status == 130)
	{
		shell->exit_status = g_status;
		g_status = 0;
	}*/
	shell->command = ft_strdup(shell->commands[i]);
	if (!init_iofiles(shell))
	{
		free(shell->command);
		return (0);
	}
	shell->command = get_real_command(shell, 0);
	if (!shell->command || !shell->command[0])
	{
		free(shell->command);
		return (0);
	}
	shell->parsed_command = ft_split_with_space(shell->command, 1);
	shell->command = shell->parsed_command[0];
	return (1);
}

void	_exec_l_cmd(t_shell *shell, int i)
{
	if (shell->commands[i])
		exec_lastcommand(shell);
	free_all(shell, 0);
}

int	__chk_empty_cmd(t_shell *shell)
{
	if (!shell->command)
	{
		shell->is_infile = 1;
		free(shell->herdoc_output);
		shell->herdoc_output = 0;
		shell->outfile = 0;
		return (1);
	}
	return (0);
}

void	__func_less_(t_shell *shell, int opt)
{
	if (!opt)
	{
		shell->is_builtin = 0;
		free(shell->parsed_command[0]);
		shell->parsed_command[0] = shell->rcommand;
	}
	else
	{
		shell->is_infile = 0;
		free_all(shell, 2);
	}
}

void	run_command(t_shell *shell)
{
	int	i;

	i = -1;
	shell->commands = ft_split_with_pipe(shell->command);
	while (shell->commands[++i] != 0)
	{
		if (init_command(shell, i) == 1)
		{
			if (!check_command(shell, i, 1))
			{
				if (__chk_empty_cmd(shell))
					continue ;
				if (!get_path(shell))
					continue ;
				__func_less_(shell, 0);
				if (shell->commands[i + 1] == 0)
					break ;
				exec_command(shell);
			}
			else
				shell->is_builtin = 1;
		}
		__func_less_(shell, 1);
	}
	_exec_l_cmd(shell, i);
}
