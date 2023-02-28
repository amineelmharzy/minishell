/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:15:30 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/26 20:09:30 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_shell *shell, char *target, char *error, int status)
{
	dup2(2, 1);
	printf("minishell: %s: %s\n", target, error);
	shell->exit_status = status;
	dup2(shell->stdout_fd, 1);
}

void	_print_error(t_shell *shell, char *error, int status)
{
	dup2(2, 1);
	printf("minishell: %s\n", error);
	shell->exit_status = status;
	dup2(shell->stdout_fd, 1);
}

int	iofiles_errors(t_shell *shell, char *set)
{
	if (count_iofiles(shell->command, set) == -1)
	{
		_print_error(shell, "syntax error near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

int	parse_error(t_shell *shell)
{
	if (count_pipes(shell->command) == -1)
	{
		_print_error(shell, "syntax error near unexpected token |", 2);
		free(shell->command);
		return (0);
	}
	if (is_fine_with_quotes(shell->command) == -1)
	{
		_print_error(shell, E_QUOT, 2);
		free(shell->command);
		return (0);
	}
	return (1);
}
