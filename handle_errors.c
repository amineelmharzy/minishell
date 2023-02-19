/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:15:30 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/20 00:33:02 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_shell *shell, char *target, char *error)
{
	dup2(2, 1);
	printf("minishell: %s: %s\n", target, error);
	dup2(shell->stdout_fd, 1);
}

int	iofiles_errors(t_shell *shell, char *set)
{
	if (count_iofiles(shell->command, set) == -1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		shell->exit_status = 2;
		return (1);
	}
	return (0);
}
