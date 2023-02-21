/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:36:08 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 11:17:08 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_absolute_path(t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_strchr(shell->command, '/'))
	{
		if (access(shell->command, F_OK) != -1)
		{
			if (access(shell->command, X_OK) != -1)
			{
				shell->rcommand = shell->command;
				return (1);
			}
			else
				print_error(shell, shell->command, strerror(errno), 126);
		}
		else
			print_error(shell, shell->command, strerror(errno), 127);
	}
	return (0);
}

int	check_rcommand(t_shell *shell)
{
	if (access(shell->rcommand, F_OK) != -1)
	{
		if (access(shell->rcommand, X_OK) != -1)
			return (1);
		else
			print_error(shell, shell->command, strerror(errno), 126);
	}
	return (0);
}

int	get_path(t_shell *shell)
{
	int	i;

	if (!shell->command)
		return (0);
	if (check_absolute_path(shell))
		return (1);
	i = 0;
	while (shell->path[i] != 0)
	{
		shell->rcommand = ft_strjoin(shell->path[i], "/");
		while ((*shell->command) != 0 && (*(shell->command) == ' '
				|| (*(shell->command) == '\t')))
			(shell->command)++;
		shell->rcommand = ft_joinstr(shell->rcommand,
				ft_strdup(shell->command));
		if (check_rcommand(shell))
			return (1);
		free (shell->rcommand);
		i++;
	}
	print_error(shell, shell->command, E_NCMD, 127);
	return (0);
}
