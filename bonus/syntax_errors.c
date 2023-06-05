/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:07:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/05 17:09:57 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_syntax_err(t_shell *shell, char **arr, int j)
{
	if (!implement_redirection(shell))
	{
		while (arr[j])
			free(arr[j++]);
		free(arr);
		return (free(shell->command), free_commands(shell, 2, 0),
			free_all(shell, 2), 1);
	}
	free(shell->command);
	free_command(shell, 0);
	return (0);
}

int	_syntax_err(t_shell *shell, char **arr, int j, int z)
{
	while (arr[j])
	{
		z = -1;
		shell->command = ft_strdup(arr[j]);
		if (parse_error(shell, 0))
		{
			while (arr[j])
				free(arr[j++]);
			return (free(arr), free_all(shell, 2), 1);
		}
		shell->commands = ft_split_with_pipe(shell->command);
		while (shell->commands[++z])
		{
			shell->command = ft_strdup(shell->commands[z]);
			if (check_redirection_syntax_err(shell, arr, j))
				return (1);
		}
		free_commands(shell, 2, 0);
		free(arr[j++]);
	}
	return (0);
}

char	*remove_par(char *str, int i)
{
	char	*res;
	int		start;

	i = 0;
	res = ft_calloc(1, 1);
	while (str[i] != 0)
	{
		start = 0;
		if (str[i] != '(' && str[i] != ')')
		{
			while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			{
				start = str[i++];
				res = ft_joinchar(res, start);
				while (str[i] && str[i] != start)
					res = ft_joinchar(res, str[i++]);
				res = ft_joinchar(res, str[i++]);
			}
			if (str[i] && str[i] != '(' && str[i] != ')')
				res = ft_joinchar(res, str[i++]);
		}
		else if (str[i])
			i++;
	}
	return (res);
}

int	syntax_err(t_shell *shell)
{
	int		i;
	char	**arr;
	char	*cmd;
	char	*save;

	i = -1;
	save = shell->command;
	shell->command = remove_par(shell->command, 0);
	shell->fcommands = ft_split_with_set(shell, shell->command, "&&");
	if (!shell->fcommands)
		return (free(save), free_all(shell, 0), 1);
	while (shell->fcommands[++i])
	{
		cmd = ft_strdup(shell->fcommands[i]);
		arr = ft_split_with_set(shell, cmd, "||");
		if (!arr)
			return (free(save), free(cmd), free_commands(shell, 0, 0), 1);
		if (_syntax_err(shell, arr, 0, -1))
			return (free(save), free_commands(shell, 0, 0), 1);
		free(arr);
	}
	free_commands(shell, 0, 0);
	shell->command = save;
	return (0);
}
