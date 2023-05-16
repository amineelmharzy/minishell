/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:07:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/16 13:20:08 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_err(t_shell *shell)
{
	int		i;

	i = -1;
	shell->commands = ft_split_with_pipe(shell->command);
	while (shell->commands[++i])
	{
		shell->command = ft_strdup(shell->commands[i]);
		if (!implement_redirection(shell))
			return (free(shell->command), 1);
		free(shell->command);
		free_outfiles(shell);
	}
	return (0);
}
