/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:42 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/22 09:59:10 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_builtin_output(t_shell *shell)
{
	if (shell->is_builtin)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
	}
}

int	_check_command(t_shell *shell, int option)
{
	if (ft_strlen(shell->command) == 4)
	{
		if (ft_strncmp(shell->command, "echo", 4) == 0)
		{
			close_builtin_output(shell);
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

int	__check_command(t_shell *shell, int option)
{
	if (ft_strlen(shell->command) == 3)
	{
		if (ft_strncmp(shell->command, "env", 3) == 0)
		{
			close_builtin_output(shell);
			run_env(shell, 0, env);
			return (1);
		}
		else if (ft_strncmp(shell->command, "pwd", 3) == 0)
		{
			close_builtin_output(shell);
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

int	check_command(t_shell *shell, int i, int option)
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
			close_builtin_output(shell);
			export(shell);
			return (1);
		}
	}
	if (_check_command(shell, option) || __check_command(shell, option))
		return (1);
	return (0);
}
