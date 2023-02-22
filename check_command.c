/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:42 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/22 12:42:37 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	_check_command(t_shell *shell, int option)
{
	if (ft_strlen(shell->command) == 4)
	{
		if (ft_strncmp(shell->command, "echo", 4) == 0)
		{
			close_builtin(shell, 0);
			run_builtin(shell, echo);
			close_builtin(shell, 1);
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
			close_builtin(shell, 0);
			run_env(shell, 0, env);
			close_builtin(shell, 1);
			return (1);
		}
		else if (ft_strncmp(shell->command, "pwd", 3) == 0)
		{
			close_builtin(shell, 0);
			run_builtin(shell, pwd);
			close_builtin(shell, 1);
			return (1);
		}
	}
	if (ft_strlen(shell->parsed_command[0]) == 2
		&& ft_strncmp(shell->parsed_command[0], "cd", 2) == 0)
	{
		run_builtin(shell, cd);
		close_builtin(shell, 1);
		return (1);
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
			run_builtin(shell, unset);
			close_builtin(shell, 1);
			return (1);
		}
	}
	if (ft_strlen(shell->parsed_command[0]) == 6)
	{
		if (ft_strncmp(shell->parsed_command[0], "export", 6) == 0)
		{
			export(shell);
			close_builtin(shell, 1);
			return (1);
		}
	}
	if (_check_command(shell, option) || __check_command(shell, option))
		return (1);
	return (0);
}
