/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:19:17 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/16 17:00:32 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_subshell_command(char *command)
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

void	__func_parse_l(char **res, char *str, int *i, int *chk)
{
	*chk = 0;
	while (str[*i] && (str[*i] == '\'' || str[*i] == '\"'))
		*res = ft_joinchar(*res, str[(*i)++]);
}

void	__until_pipe(t_shell *shell, char **res, char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	while (str[*i] != 0 && str[*i] != '|')
	{
		shell->s_iofiles = ft_joinchar(shell->s_iofiles,
				str[(*i)++]);
	}
}

void	__func_parse(t_shell *shell, char **res, char *str, int *i)
{
	int	chk;
	int	count_open;
	int	count_close;

	count_open = 0;
	count_close = 0;
	while (str[*i] != 0)
	{
		__func_parse_l(res, str, i, &chk);
		if (str[*i] == '(')
			if (++count_open == 1)
				chk = ++(*i);
		if (str[*i] == ')')
		{
			if (++count_close == count_open)
			{
				chk = (*i)++;
				__until_pipe(shell, res, str, i);
				break ;
			}
		}
		if (str[*i] && str[*i] != '\'' && str[*i] != '\"' && !chk)
			*res = ft_joinchar(*res, str[(*i)++]);
	}
}
