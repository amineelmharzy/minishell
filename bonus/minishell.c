/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:41:01 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/12 08:47:14 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		//g_status = 130;
		printf("\n");
	}
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	if (ac > 2)
	{
		if (ft_strncmp(av[1], "-c", 2) == 0)
		{
			shell.command = ft_strdup(av[2]);
			run_command(&shell);
			exit(shell.exit_status);
		}
	}
	while (1)
	{
		init_prompt(&shell);
		shell.command = readline(shell.prompt);
		add_history(shell.command);
		if (shell.command)
		{
			run_command(&shell);
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
