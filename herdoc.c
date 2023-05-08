/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:30:11 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/06 15:38:26 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *s)
{
	char	*res;
	int		i;

	res = ft_calloc(1, 1);
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != '\'' && s[i] != '\"')
			res = ft_joinchar(res, s[i]);
		i++;
	}
	free(s);
	return (res);
}	

void	read_herdoc(t_shell *shell, char **output, char **cmp, int *i)
{
	while (shell->herdocs[++(*i)] != 0)
	{
		shell->command = readline("> ");
		free(*output);
		*output = ft_calloc(1, 1);
		while (shell->command)
		{
			*cmp = remove_quotes(ft_strdup(shell->herdocs[*i]));
			if (ft_strlen(shell->command) == ft_strlen(*cmp)
				&& ft_strncmp(shell->command, *cmp,
					ft_strlen(shell->command)) == 0)
			{
				free(shell->command);
				free(*cmp);
				break ;
			}
			if (!shell->is_quoted_herdoc)
				*output = ft_joinstr(*output, get_real_command(shell, -1));
			else
				*output = ft_joinstr(*output, shell->command);
			*output = ft_joinchar(*output, '\n');
			free(*cmp);
			shell->command = readline("> ");
		}
	}
}

char	*herdoc(t_shell *shell)
{
	int		i;
	char	*output;
	char	*save;
	char	*cmp;

	i = -1;
	output = ft_calloc(1, 1);
	free(shell->command);
	save = ft_strdup(shell->command);
	read_herdoc(shell, &output, &cmp, &i);
	shell->command = save;
	if (!shell->command[0])
		free(shell->command);
	return (output);
}
