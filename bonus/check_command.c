/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:42 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/07 18:39:58 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_command__(t_shell *shell, int option, int i)
{
	if (ft_strncmp(shell->command, "exit", 4) == 0)
	{
		if (i == 0 && shell->commands[i] != 0)
		{
			if (shell->parsed_command[1])
			{
				shell->exit_status = ft_atoi(shell, shell->parsed_command[1],
						shell->parsed_command[2]);
				if (shell->exit_status != -1)
					exit(shell->exit_status);
				else
					shell->exit_status = 1;
			}
			else
			{
				exit(shell->exit_status);
			}
			return (1);
		}
		run_builtin(shell, _exit_, 1);
		close_builtin(shell, 1);
		return (1);
	}
	return (0);
}

int	_check_command(t_shell *shell, int option, int i)
{
	if (ft_strlen(shell->command) == 4)
	{
		if (ft_strncmp(shell->command, "echo", 4) == 0)
		{
			close_builtin(shell, 0);
			run_builtin(shell, echo, 1);
			close_builtin(shell, 1);
			shell->exit_status = 0;
			return (1);
		}
		return (_check_command__(shell, option, i));
	}
	return (0);
}

int	__check_command__(t_shell *shell, int option, int i)
{
	if (ft_strlen(shell->parsed_command[0]) == 2
		&& ft_strncmp(shell->parsed_command[0], "cd", 2) == 0)
	{
		if (shell->is_pipe || i != 0)
		{
			run_builtin(shell, cd, 1);
			close_builtin(shell, 1);
		}
		else
		{
			run_builtin(shell, cd, 0);
			close_builtin(shell, 1);
		}
		return (1);
	}
	return (0);
}

int	__check_command(t_shell *shell, int option, int i)
{
	if (ft_strlen(shell->command) == 3)
	{
		if (ft_strncmp(shell->command, "env", 3) == 0)
		{
			close_builtin(shell, 0);
			run_env(shell, 0, env);
			shell->exit_status = 0;
			close_builtin(shell, 1);
			return (1);
		}
		else if (ft_strncmp(shell->command, "pwd", 3) == 0)
		{
			close_builtin(shell, 0);
			run_builtin(shell, pwd, 1);
			close_builtin(shell, 1);
			return (1);
		}
	}
	if (__check_command__(shell, option, i))
		return (1);
	return (0);
}

int	check_command(t_shell *shell, int i, int option)
{
	shell->is_pipe = 0;
	if (shell->commands[i + 1] != 0)
		shell->is_pipe = 1;
	if (ft_strlen(shell->parsed_command[0]) == 5
		&& ft_strncmp(shell->parsed_command[0], "unset", 5) == 0)
	{
		run_builtin(shell, unset, 0);
		close_builtin(shell, 1);
		return (1);
	}
	if (ft_strlen(shell->parsed_command[0]) == 6)
	{
		if (ft_strncmp(shell->parsed_command[0], "export", 6) == 0)
		{
			if (shell->parsed_command[1])
				run_builtin(shell, export, 0);
			else
				export(shell);
			close_builtin(shell, 1);
			return (1);
		}
	}
	if (_check_command(shell, option, i) || __check_command(shell, option, i))
		return (1);
	return (0);
}
