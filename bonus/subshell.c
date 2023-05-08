/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:57:25 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/08 16:48:14 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_p(t_shell *shell, char *str, char **save)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(1, 1);
	shell->s_iofiles = ft_calloc(1, 1);
	while (str[i] != 0)
	{
		skip_quotes(str, &i);
		if (str[i] == '(')
			break ;
		*save = ft_joinchar(*save, str[i++]);
	}
	__func_parse(shell, &res, str, &i);
	while (str[i] != 0)
	{
		if (str[i] == '|' && str[i + 1] && str[i + 1] != '|' && !shell->is_pipe)
		{
			shell->is_pipe = 1;
			i++;
		}
		else
			*save = ft_joinchar(*save, str[i++]);
	}
	return (res);
}

void	_subshell_func(t_shell *shell, char ***ars, char **cmd, char **save)
{
	char	*command;

	*save = ft_calloc(1, 1);
	command = remove_p(shell, *cmd, save);
	free(*cmd);
	*cmd = *save;
	*ars = ft_calloc(4, sizeof(char *));
	if (!ars)
		return ;
	(*ars)[0] = ft_strjoin("./", shell->shell_name);
	(*ars)[1] = ft_strdup("-c");
	(*ars)[2] = command;
	(*ars)[3] = 0;
}

void	_subshell_child(t_shell *shell, char **ars, int pfd[2])
{
	int	i;

	i = 0;
	if (shell->is_pipe == 1)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
	}
	shell->command = shell->s_iofiles;
	if (!init_iofiles(shell))
	{
		free(shell->command);
		return ;
	}
	shell->rcommand = ars[0];
	shell->parsed_command = ars;
	exec_lastcommand(shell);
	free_commands(shell, 0, 0);
	free_all(shell, 1);
	exit(shell->exit_status);
}

void	_subshell_parent(t_shell *shell, char **ars, char **cmd, char *save)
{
	int	status;
	int	i;

	i = 0;
	if (!shell->is_pipe)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
	}
	shell->is_pipe = 0;
	*cmd = save;
	while (ars[i])
		free(ars[i++]);
	free(ars);
}
