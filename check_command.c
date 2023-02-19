/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:42 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/17 17:59:46 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(t_shell *shell)
{
	if (ft_strlen(shell->command) == 4)
	{
		if (ft_strncmp(shell->command, "echo", 4) == 0)
		{
			echo(shell);
			return (1);
		}
		if (ft_strncmp(shell->command, "exit", 4) == 0)
		{
			exit(0);
			return (1);
		}
	}
	if (ft_strlen(shell->command) == 3)
	{
		if (ft_strncmp(shell->command, "env", 3) == 0)
		{
			env(shell, 0);
			return (1);
		}
		else if (ft_strncmp(shell->command, "pwd", 3) == 0)
		{
			pwd(shell);
			return (1);
		}
	}
	if (ft_strlen(shell->real_command[0]) == 2)
	{
		if (ft_strncmp(shell->real_command[0], "cd", 2) == 0)
		{
			cd(shell);
			return (1);
		}
	}
	if (ft_strlen(shell->real_command[0]) == 5)
	{
		if (ft_strncmp(shell->real_command[0], "unset", 5) == 0)
		{
			unset(shell);
			return (1);
		}
	}
	if (ft_strlen(shell->real_command[0]) == 6)
	{
		if (ft_strncmp(shell->real_command[0], "export", 6) == 0)
		{
			export(shell);
			return (1);
		}
	}
	return (0);
}
