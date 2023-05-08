/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:36:08 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/07 17:07:34 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_absolute_path(t_shell *shell, int opt)
{
	DIR	*d;

	if (ft_strchr(shell->command, '/'))
	{
		if (access(shell->command, F_OK) != -1)
		{
			d = opendir(shell->command);
			if (d)
			{
				closedir(d);
				print_error(shell, shell->command, E_IDIR, 126);
				return (-1);
			}
			if (access(shell->command, X_OK) != -1)
			{
				if (opt)
					shell->rcommand = ft_strdup(shell->command);
				return (1);
			}
			print_error(shell, shell->command, strerror(errno), 126);
		}
		print_error(shell, shell->command, strerror(errno), 127);
		return (-1);
	}
	return (0);
}

int	check_rcommand(t_shell *shell, int i)
{
	shell->rcommand = ft_strjoin(shell->path[i], "/");
	shell->rcommand = ft_joinstr(shell->rcommand,
			ft_strdup(shell->command));
	if (access(shell->rcommand, F_OK) != -1)
	{
		if (access(shell->rcommand, X_OK) != -1)
			return (1);
		else
			print_error(shell, shell->command, strerror(errno), 126);
		return (2);
	}
	return (0);
}

int	check_errors(t_shell *shell, int option)
{
	if (option == 0)
	{
		if (!shell->command && !shell->herdocs)
			return (0);
		if (!shell->command[0])
		{
			print_error(shell, shell->command, E_NCMD, 127);
			close(0);
			dup2(shell->stdin_fd, 0);
			return (0);
		}
		if (check_absolute_path(shell, 0) == -1)
			return (0);
		return (1);
	}
	if (!shell->path || !shell->path[0])
	{
		print_error(shell, shell->command, E_NFOD, 127);
		close(0);
		dup2(shell->stdin_fd, 0);
		return (0);
	}
	return (1);
}

int	get_path(t_shell *shell)
{
	int		i;
	int		ret;

	if (!check_errors(shell, 0))
		return (0);
	if (check_absolute_path(shell, 1))
		return (1);
	if (!check_errors(shell, 1))
		return (0);
	i = -1;
	while (shell->path[++i] != 0)
	{
		ret = check_rcommand(shell, i);
		if (ret)
			return (1);
		else if (ret == 2)
			break ;
		free (shell->rcommand);
	}
	if (ret != 2)
		print_error(shell, shell->command, E_NCMD, 127);
	close(0);
	dup2(shell->stdin_fd, 0);
	return (0);
}
