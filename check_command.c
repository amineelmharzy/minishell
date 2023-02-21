/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:42 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 18:08:55 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_command(t_shell *shell)
{
	if (ft_strlen(shell->command) == 4)
	{
		if (ft_strncmp(shell->command, "echo", 4) == 0)
		{
			run_builtin(shell, echo);
			return (1);
		}
		if (ft_strncmp(shell->command, "exit", 4) == 0)
		{
			exit(0);
		}
	}
	return (0);
}

int	__check_command(t_shell *shell)
{
	if (ft_strlen(shell->command) == 3)
	{
		if (ft_strncmp(shell->command, "env", 3) == 0)
		{
			run_env(shell, env);
			return (1);
		}
		else if (ft_strncmp(shell->command, "pwd", 3) == 0)
		{
			run_builtin(shell, pwd);
			return (1);
		}
	}
	if (ft_strlen(shell->parsed_command[0]) == 2)
	{
		if (ft_strncmp(shell->parsed_command[0], "cd", 2) == 0)
		{
			cd(shell);
			return (1);
		}
	}
	return (0);
}

int	check_command(t_shell *shell, int i)
{
	shell->is_pipe = 0;
	if (shell->commands[i + 1] != 0)
		shell->is_pipe = 1;
	if (ft_strlen(shell->parsed_command[0]) == 5)
	{
		if (ft_strncmp(shell->parsed_command[0], "unset", 5) == 0)
		{
			unset(shell);
			return (1);
		}
	}
	if (ft_strlen(shell->parsed_command[0]) == 6)
	{
		if (ft_strncmp(shell->parsed_command[0], "export", 6) == 0)
		{
			run_builtin(shell, export);
			return (1);
		}
	}
	if (_check_command(shell) || __check_command(shell))
		return (1);
	return (0);
}
