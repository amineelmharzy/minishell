/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:16:18 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/10 16:31:44 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthis(char	*command)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (command[i] != 0)
	{
		while (command[i] == '\'' || command[i] == '\"')
		{
			start = command[i++];
			while (command[i] && command[i] != start)
				i++;
			i++;
		}
		if (command[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_p(char *str)
{
	char	*res;
	int		i;
	int		count_open = 0;
	int		count_close = 0;

	i = 0;
	res = ft_calloc(1, 1);
	while (str[i] != 0)
	{
		if (str[i] == '(')
		{
			count_open++;
			if (count_open == 1)
				i++;
		}
		if (str[i] == ')')
		{
			count_close++;
			if (count_close == 1)
				i++;
		}
		else
			res = ft_joinchar(res, str[i++]);
	}
	return (res);
}

void	_run_command(t_shell *shell, char *command)
{
	command = remove_p(command);
	char	**ars = ft_calloc(4, sizeof(char *));
	int	pfd[2];
	pipe(pfd);
	ars[0] = ft_strdup("./minishell");
	ars[1] = ft_strdup("-c");
	ars[2] = command;
	ars[3] = 0;
	int	pid = fork();
	if (!pid)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
		execve(ars[0], ars, shell->envp);
		close(pfd[1]);
	}
	else
	{
		waitpid(-1, NULL, 0);
		dup2(pfd[0], 0);
		close(pfd[1]);
		/*
		ars[0] = ft_strdup("/usr/bin/nl");
		ars[1] = 0;
		execve(ars[0], ars, NULL);
		exit(0);
		*/
	}
}


void	run_command(t_shell *shell)
{
	int	i;
	int	j;
	int	z;

	shell->fcommands = ft_split_with_set(shell->command, "&&");
	j = 0;
	while (shell->fcommands[j])
	{
		/*
		if (check_parenthis(shell->fcommands[j]))
			_run_command(shell, shell->fcommands[j]);
			*/
		shell->or_commands = ft_split_with_set(shell->fcommands[j], "||");
		z = 0;
		while (shell->or_commands[z])
		{
			if (parse_error(shell))
				return ;
			__run_command(shell, shell->or_commands[z]);
			z++;
			if (shell->exit_status == 0)
				break ;
		}
		j++;
	}
}
