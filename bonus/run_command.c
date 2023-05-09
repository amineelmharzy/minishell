/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:16:18 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/08 19:17:18 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_run_command(t_shell *shell, char **cmd)
{
	char	**ars;
	char	*save;
	int		pfd[2];
	int		pid;
	int		status;

	_subshell_func(shell, &ars, cmd, &save);
	pipe(pfd);
	pid = fork();
	if (!pid)
		_subshell_child(shell, ars, pfd);
	else
	{
		if (shell->is_pipe == 1)
		{
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
		waitpid(pid, &status, 0);
		shell->exit_status = WEXITSTATUS(status);
		_subshell_parent(shell, ars, cmd, save);
	}
}

void	_run_command_(t_shell *shell, int z)
{
	int	j;

	j = -1;
	while (shell->fcommands[++j])
	{
		shell->command = ft_strdup(shell->fcommands[j]);
		shell->or_commands = ft_split_with_set(shell, shell->command, "||");
		if (!shell->or_commands)
			return ;
		z = -1;
		while (shell->or_commands[++z])
		{
			if (is_subshell_command(shell->or_commands[z]))
				_run_command(shell, &shell->or_commands[z]);
			shell->command = ft_strdup(shell->or_commands[z]);
			if (parse_error(shell, 0))
				return (free_commands(shell, 1, 0));
			__run_command(shell, shell->command, z);
			if (shell->exit_status == 0)
				break ;
		}
		free_commands(shell, 1, 0);
		if (shell->exit_status != 0)
			break ;
	}
}

void	run_command(t_shell *shell)
{
	if (parse_error(shell, 1))
		return (free_all(shell, 0));
	shell->fcommands = ft_split_with_set(shell, shell->command, "&&");
	if (!shell->fcommands)
		return (free(shell->command), free_all(shell, 0));
	if (syntax_err(shell))
		return (free_all(shell, 0));
	_run_command_(shell, -1);
	free_all(shell, 0);
}
