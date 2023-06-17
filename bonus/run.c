/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 11:39:20 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_exec_l_cmd(t_shell *shell, int i)
{
	if (shell->commands[i])
		exec_lastcommand(shell);
	free_all(shell, 2);
	if (shell->commands)
	{
		i = 0;
		while (shell->commands[i])
			free(shell->commands[i++]);
		free(shell->commands);
	}
}

int	__chk_empty_cmd(t_shell *shell)
{
	if (!shell->command)
	{
		shell->is_infile = 1;
		shell->ifile = 0;
		shell->outfile = 0;
		return (1);
	}
	return (0);
}

int	__func_less_(t_shell *shell, int opt)
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
	return (0);
}

void	__run_command(t_shell *shell, char *command, int i)
{
	i = -1;
	shell->commands = ft_split_with_pipe(command);
	while (shell->commands[++i] != 0)
	{
		if (init_command(shell, i) == 1)
		{
			if (!check_command(shell, i, 1))
			{
				if (__chk_empty_cmd(shell))
					continue ;
				if (is_subshell_command(shell->commands[i]))
					_run_command(shell, &shell->commands[i]);
				else
				{
					if (!get_path(shell))
						continue ;
					if (__func_less_(shell, 0) || !shell->commands[i + 1])
						break ;
					exec_command(shell);
				}
			}
		}
		__func_less_(shell, 1);
	}
	_exec_l_cmd(shell, i);
}
