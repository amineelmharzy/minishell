/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:07:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/08 19:16:08 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (!implement_redirection(shell))
			{
				while (arr[j])
					free(arr[j++]);
				free(arr);
				return (free_commands(shell, 2, 0), free_all(shell, 2), 1);
			}
		}
		free_commands(shell, 2, 0);
		free(arr[j++]);
	}
	return (0);
}

int	syntax_err(t_shell *shell)
{
	int		i;
	int		j;
	char	**arr;
	char	*cmd;

	i = -1;
	while (shell->fcommands[++i])
	{
		j = 0;
		cmd = ft_strdup(shell->fcommands[i]);
		arr = ft_split_with_set(shell, cmd, "||");
		if (!arr)
			return (free(cmd), 1);
		if (_syntax_err(shell, arr, j, -1))
			return (1);
		free(arr);
		cmd = shell->command;
		shell->command = cmd;
	}
	return (0);
}
