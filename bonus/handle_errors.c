/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:15:30 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/14 15:41:17 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_shell *shell, char *target, char *error, int status)
{
	write(2, "minishell: ", 11);
	write(2, target, ft_strlen(target));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	shell->exit_status = status;
}

char	**_print_error(t_shell *shell, char *error, int status)
{
	write(2, "minishell: ", 11);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	shell->exit_status = status;
	return (NULL);
}

int	iofiles_errors(t_shell *shell, char *set)
{
	if (count_iofiles(shell->command, set) == -1)
	{
		_print_error(shell, "syntax error near unexpected token `newline'", 2);
		dup2(shell->stdin_fd, 0);
		return (1);
	}
	return (0);
}

int	parse_error(t_shell *shell, int option)
{
	if (!option && count_pipes(shell->command) == -1)
	{
		_print_error(shell, "syntax error near unexpected token |", 2);
		free(shell->command);
		shell->command = 0;
		return (1);
	}
	if (is_fine_with_quotes(shell->command) == -1)
	{
		_print_error(shell, E_QUOT, 2);
		free(shell->command);
		shell->command = 0;
		return (1);
	}
	if (option && check_parenthesis(shell->command) == -1)
	{
		_print_error(shell, E_PARN, 2);
		shell->command = 0;
		return (1);
	}
	return (0);
}
