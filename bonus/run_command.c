/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:16:18 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/12 11:05:37 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_subshell_command(char *command)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (command[i] == ' ')
		i++;
	if (command[i] == '(')
		return (1);
	return (0);
}

void	__func_parse(t_shell *shell, char **res, char *str, int *i)
{
	int	chk;
	int	count_open;
	int	count_close;

	chk = 0;
	count_open = 0;
	count_close = 0;
	while (str[*i] != 0)
	{
		chk = 0;
		skip_quotes(str, i);
		if (str[*i] == '(')
			if (++count_open == 1)
				chk = ++(*i);
		if (str[*i] == ')')
		{
			if (++count_close == count_open)
			{
				chk = (*i)++;
				while (str[*i] != 0 && str[*i] != '|')
					shell->subshell_iofiles = ft_joinchar(shell->subshell_iofiles, str[(*i)++]);
				break;
			}
		}
		if (str[*i] && !chk)
			*res = ft_joinchar(*res, str[(*i)++]);
	}
}

char	*remove_p(t_shell *shell, char *str, char **save)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(1, 1);
	shell->subshell_iofiles = ft_calloc(1, 1);
	while (str[i] != 0)
	{
		skip_quotes(str, &i);
		if (str[i] == '(')
			break;
		*save = ft_joinchar(*save, str[i++]);
	}
	__func_parse(shell, &res, str, &i);
	while (str[i] != 0)
	{
		if (str[i] == '|' && str[i + 1] && str[i + 1] != '|')
		{
			shell->is_pipe = 1;
			i++;
		}
		else
			*save = ft_joinchar(*save, str[i++]);
	}
	return (res);
}

void	_subshell_child(t_shell *shell, char **cmd, char *save)
{
	int	status;

	waitpid(-1, &status, 0);
	if (shell->is_pipe == 1)
	{
		dup2(pfd[0], 0);
		close(pfd[1]);
	}
	else
	{
		close(0);
		dup2(shell->stdin_fd, 0);
	}
	shell->is_pipe = 0;
	*cmd = save;
	shell->exit_status = WEXITSTATUS(status);
}

void	_run_command(t_shell *shell, char **cmd)
{
	char	*save = ft_calloc(1,1);
	char *command = remove_p(shell, *cmd, &save);
	*cmd = save;
	char	**ars = ft_calloc(4, sizeof(char *));
	int	pfd[2];
	int	status;
	pipe(pfd);
	ars[0] = ft_strdup("./minishell");
	ars[1] = ft_strdup("-c");
	ars[2] = command;
	ars[3] = 0;
	int	pid = fork();
	if (!pid)
	{
		if (shell->is_pipe == 1)
		{
			dup2(pfd[1], 1);
			close(pfd[0]);
		}
		shell->command = shell->subshell_iofiles;
		if (!init_iofiles(shell))
			printf("Error\n");
		shell->rcommand = ars[0];
		shell->parsed_command = ars;
		exec_lastcommand(shell);
		exit(shell->exit_status);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (shell->is_pipe == 1)
		{
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
		else
		{
			close(0);
			dup2(shell->stdin_fd, 0);
		}
		shell->is_pipe = 0;
		*cmd = save;
		shell->exit_status = WEXITSTATUS(status);
	}
}

void	run_command(t_shell *shell)
{
	int	i;
	int	j;
	int	z;

	if (parse_error(shell, 1))
		return ;
	shell->fcommands = ft_split_with_set(shell, shell->command, "&&");
	if (!shell->fcommands)
		return ;
	j = 0;
	while (shell->fcommands[j])
	{
		shell->command = shell->fcommands[j];
		shell->or_commands = ft_split_with_set(shell, shell->command, "||");
		if (!shell->or_commands)
			return ;
		z = 0;
		while (shell->or_commands[z])
		{
			if (is_subshell_command(shell->or_commands[z]))
				_run_command(shell, &shell->or_commands[z]);
			shell->command = ft_strdup(shell->or_commands[z]);
			/*
			if (parse_error(shell, 0))
				return ;
			__run_command(shell, shell->command);
			if (shell->exit_status == 0)
				break ;
			*/
			z++;
		}
		if (shell->exit_status != 0)
			break ;
		j++;
	}
}
