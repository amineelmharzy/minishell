/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/20 00:28:44 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->command[0])
		return ;
	if (count_pipes(shell->command) == -1)
	{
		printf("Minishell : syntax error near unexpected token | \n");
		shell->exit_status = 2;
		return ;
	}
	if (is_fine_with_quotes(shell->command) == -1)
	{
		printf("Minishell : quote error\n");
		shell->exit_status = 1;
		return ;
	}
	shell->commands = ft_split_with_pipe(shell->command);
	int	j = 0;
	while (shell->commands[i] != 0)
	{
		j = 0;
		shell->command = shell->commands[i];
		shell->command = get_real_command(shell);
		if (!implement_redirection(shell))
			return ;
		if (!check_infiles(shell))
			return ;
		if (shell->herdocs)
			shell->herdoc_output = herdoc(shell);
		if (shell->outfiles || shell->afiles)
			if (!init_outfiles(shell))
				return ;
		shell->real_command = ft_split_with_space(shell->command);
		shell->command = shell->real_command[0];
		/*
		if (check_command(shell))
			return ;
		*/
		if (!get_path(shell))
			return ;
		shell->real_command[0] = shell->rcommand;
		if (shell->real_command)
		{
			while (shell->real_command[j] != 0)
			{
				free(shell->real_command[j]);
				j++;
			}
			free(shell->real_command);
		}
		free(shell->command);
		/*
		if (shell->commands[i + 1] == 0)
			break ;
		exec_command(shell);
		*/
		i++;
	}
	//free_all(shell, 1);
	/*
	ecev_lastcommand(shell);
	*/
	free_all(shell, 0);
	//while (1);
}

/*
void	handle(int sig)
{
	if (sig == SIGINT)
	{
		(void) sig;
	}
	if (sig == SIGQUIT)
	{
		(void) sig;
	}
}
*/

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	shell.envp = envp;
	shell.path = ft_split(getenv("PATH"), ':');
	shell.exit_status = 0;
	shell.prompt = "~ ";
	shell.herdocs = 0;
	shell.herdoc_output = 0;
	shell.infiles = 0;
	shell.outfiles= 0;
	shell.afiles = 0;
	shell.infile = 0;
	shell.outfile = 0;
	shell.stdin_fd = dup(0);
	shell.stdout_fd = dup(1);
	init_env(&shell);
	int	i;
	i = 0;
	while (1)
	{
		shell.command = readline(shell.prompt);
		add_history(shell.command);
		if (shell.command)
			run_command(&shell);
		else
		{
			free_all(&shell, 1);
			exit(0);
		}
	}
	free_all(&shell, 1);
	return (0);
}
