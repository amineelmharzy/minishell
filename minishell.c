/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:41:01 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/11 19:09:59 by ael-mhar         ###   ########.fr       */
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
	while (1)
	{
		init_prompt(&shell);
		shell.command = readline("# ");
		add_history(shell.command);
		if (shell.command)
		{
			if (!parse_error(&shell))
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
