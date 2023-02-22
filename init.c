/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:48 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command(t_shell *shell, int i)
{
	shell->command = shell->commands[i];
	shell->command = get_real_command(shell);
	if (!init_iofiles(shell))
	{
		free_all(shell, 0);
		return (0);
	}
	shell->parsed_command = ft_split_with_space(shell->command);
	if (!shell->parsed_command)
		return (0);
	return (1);
}

void	_exec_l_cmd(t_shell *shell, int i)
{
	if (shell->commands[i])
		exec_lastcommand(shell);
}

void	run_command(t_shell *shell)
{
	int	i;

	if (!parse_error(shell))
		return ;
	i = -1;
	shell->commands = ft_split_with_pipe(shell->command);
	while (shell->commands[++i] != 0)
	{
		if (!init_command(shell, i))
			return ;
		shell->command = shell->parsed_command[0];
		if (!check_command(shell, i, 1))
		{
			if (!get_path(shell))
				return ;
			shell->is_builtin = 0;
			shell->parsed_command[0] = shell->rcommand;
			if (shell->commands[i + 1] == 0)
				break ;
			exec_command(shell);
		}
		else
			shell->is_builtin = 1;
	}
	if (shell->commands[i])
		_exec_l_cmd(shell, i);
}

void	handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		shell.command = readline(shell.prompt);
		add_history(shell.command);
		if (shell.command)
			run_command(&shell);
		else
		{
			exit(0);
		}
	}
	free_all(&shell, 1);
	return (0);
}
