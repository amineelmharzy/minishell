/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/18 20:07:17 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->command[0])
		return ;
	shell->command = get_real_command(shell);
	printf("%s\n", shell->command);
	free(shell->command);
	/*
	shell->commands = ft_split_with_pipe(shell->command);
	if (count_pipes(shell->command) == -1)
	{
		printf("Minishell : syntax error near unexpected token | \n");
		shell->exit_status = 258;
		return ;
	}
	if (is_fine_with_quotes(shell->command) == -1)
	{
		printf("Minishell : quote error\n");
		shell->exit_status = 258;
		return ;
	}
	while (shell->commands[i] != 0)
	{
		shell->command = shell->commands[i];
		shell->outfile = 0;
		shell->infiles = 0;
		shell->herdocs = 0;
		shell->outfiles = 0;
		shell->afiles = 0;
		shell->command = get_real_command(shell);
		if (!implement_redirection(shell))
		{
			shell->exit_status = 258;
			return ;
		}
		if (!check_infiles(shell))
			return ;
		if (shell->herdocs)
			shell->herdoc_output = herdoc(shell);
		if (shell->outfiles || shell->afiles)
			if (!init_outfiles(shell))
				return ;
		shell->real_command = ft_split_with_space(shell->command);
		shell->command = shell->real_command[0];
		if (check_command(shell))
			return ;
		if (!get_path(shell))
			return ;
		shell->real_command[0] = shell->rcommand;
		if (shell->commands[i + 1] == 0)
			break ;
		exec_command(shell);
		i++;
	}
	ecev_lastcommand(shell);
	*/
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
			exit(0);
	}
	while (shell.path[i])
		free(shell.path[i++]);
	free(shell.path);
	free_env(&shell);
	while (1);
}
