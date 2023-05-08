/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:54:43 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/07 15:59:26 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] != 0)
		return (0);
	return (1);
}

int	_check_space(char *str, int i)
{
	int	st;

	st = 0;
	while (str[i] != 0)
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			while (str[i] == '\'')
			{
				st = str[i++];
				while (str[i] && str[i] != st)
					i++;
				i++;
			}
			if (str[i] != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	__check_space(char *str, int *i, int *j, int *len)
{
	int	st;

	while (str[(*i)] == ' ')
	{
		(*i)++;
		(*j)++;
	}
	if (!str[*i] || str[*i] == ' ')
		return (1);
	while (str && (str[*i] == '\"' || str[*i] == '\''))
	{
		st = str[(*i)++];
		while (str[(*i)] && str[*i] != st)
		{
			(*len)++;
			(*i)++;
		}
		(*i)++;
	}
	return (0);
}

int	check_spaces(char *str, char *file)
{
	int	i;
	int	st;
	int	j;
	int	len;

	i = 0;
	st = 0;
	len = 0;
	j = 0;
	if (!str || !str[0])
		return (0);
	if (__check_space(str, &i, &j, &len))
		return (1);
	if (len == 0)
	{
		st = 0;
		if (!str[i] && j)
			return (1);
		while (str[i] && str[i++] == ' ')
			st++;
		if (str[i] == 0 && st)
			return (1);
	}
	return (_check_space(str, i));
}

int	check_ambiguous_redirect(t_shell *shell, char **iofile)
{
	int		i;
	char	*save;

	i = 0;
	save = shell->command;
	shell->command = *iofile;
	shell->command = get_real_command(shell, 0);
	if (!shell->command || !shell->command[0] || check_spaces(shell->command,
			*iofile))
	{
		print_error(shell, *iofile, E_AMBR, 1);
		*iofile = remove_spaces(shell->command);
		return (shell->exit_status = 1, 1);
	}
	*iofile = remove_spaces(shell->command);
	shell->command = remove_quotes(shell->command);
	if (!shell->command[0])
	{
		print_error(shell, shell->command, E_NOTF, 1);
		shell->exit_status = 1;
		return (1);
	}
	free(shell->command);
	shell->command = save;
	return (0);
}
