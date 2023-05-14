/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:07:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/13 14:27:59 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_err(t_shell *shell)
{
	char	*save;
	int		i;

	i = -1;
	save = shell->command;
	shell->commands = ft_split_with_pipe(ft_strdup(shell->command));
	while (shell->commands[++i])
	{
		shell->command = ft_strdup(shell->commands[i]);
		if (!implement_redirection(shell))
			return (free(shell->command), free(save), 1);
		free(shell->command);
		free_outfiles(shell);
	}
	shell->command = save;
	return (0);
}
