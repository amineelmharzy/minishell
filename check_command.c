/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:42 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/29 16:47:57 by ael-mhar         ###   ########.fr       */
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
		else if (ft_strncmp(shell->command, "exit", 4) == 0)
		{
			exit(0);
			return (1);
		}
	}
	else if (ft_strlen(shell->command) == 3)
	{
		if (ft_strncmp(shell->command, "env", 3) == 0)
		{
			env(shell);
			return (1);
		}
	}
	else if (ft_strlen(shell->parsed_command[0]) == 2)
	{
		if (ft_strncmp(shell->parsed_command[0], "cd", 2) == 0)
		{
			cd(shell);
			return (1);
		}
	}
	else if (ft_strlen(shell->parsed_command[0]) == 6)
	{
		if (ft_strncmp(shell->parsed_command[0], "export", 6) == 0)
		{
			export(shell);
			return (1);
		}
	}
	return (0);
}
