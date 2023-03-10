/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:36:08 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/09 19:09:47 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__func(t_shell *shell, DIR *d, int ret, int option)
{
	char	*_var;

	if (!option)
	{
		chdir(shell->command);
		shell->exit_status = 0;
		is_env(shell, "PWD", 3, 0);
		getcwd(shell->cwd, sizeof(shell->cwd));
		add_env_var(shell, ft_strjoin("PWD=", shell->cwd), 0);
		closedir(d);
	}
	else
	{
		if (ret == 1)
		{
			is_env(shell, "_", 1, 0);
			_var = ft_strjoin("_=", shell->rcommand);
			add_env_var(shell, _var, 0);
			free(_var);
			return (1);
		}
	}
	return (0);
}

int	check_absolute_path(t_shell *shell)
{
	DIR	*d;

	if (ft_strchr(shell->command, '/'))
	{
		if (access(shell->command, F_OK) != -1)
		{
			d = opendir(shell->command);
			if (d)
			{
				__func(shell, d, 0, 0);
				return (-1);
			}
			if (access(shell->command, X_OK) != -1)
			{
				shell->rcommand = ft_strdup(shell->command);
				return (1);
			}
			else
				print_error(shell, shell->command, strerror(errno), 126);
		}
		else
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
			return (0);
		}
		if (check_absolute_path(shell) == -1)
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
	if (check_absolute_path(shell))
		return (1);
	if (!check_errors(shell, 1))
		return (0);
	i = -1;
	while (shell->path[++i] != 0)
	{
		ret = check_rcommand(shell, i);
		if (__func(shell, NULL, ret, 1))
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
