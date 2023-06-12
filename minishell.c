/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:41:01 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/12 10:43:33 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command(t_shell *shell, int i)
{
	shell->parsed_command = 0;
	if (g_status == 1)
	{
		shell->exit_status = g_status;
		g_status = 0;
	}
	shell->command = ft_strdup(shell->commands[i]);
	if (!init_iofiles(shell))
	{
		free(shell->command);
		return (dup2(shell->stdin_fd, 0), 0);
	}
	shell->command = get_real_command(shell, 0);
	if (!shell->command || !shell->command[0])
	{
		if (shell->command)
			free(shell->command);
		return (0);
	}
	shell->parsed_command = ft_split_with_space(shell->command, 1);
	shell->command = shell->parsed_command[0];
	if (!shell->command)
		dup2(shell->stdin_fd, 0);
	return (1);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 1;
		printf("\n");
	}
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void) ac;
	(void) av;
	init_shell(&shell, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		shell.command = readline("▶ ");
		add_history(shell.command);
		if (shell.command)
		{
			if (!parse_error(&shell))
				run_command(&shell, -1);
			free_all(&shell, 0);
		}
		else
		{
			free_all(&shell, 1);
			exit(shell.exit_status);
		}
	}
	return (0);
}
