/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:30:11 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 11:52:37 by ael-mhar         ###   ########.fr       */
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
	res = ft_joinchar(res, '\n');
	free(s);
	return (res);
}

void	_free_command(char **command, char *s)
{
	free(*command);
	*command = 0;
	free(s);
}

void	read_herdoc(t_shell *shell, char **output, char **cmp, int *i)
{
	while (shell->herdocs[++(*i)] != 0)
	{
		shell->command = get_next_line(0);
		free(*output);
		*output = ft_calloc(1, 1);
		while (shell->command)
		{
			*cmp = remove_quotes(ft_strdup(shell->herdocs[*i]));
			if (ft_strlen(shell->command) == ft_strlen(*cmp)
				&& ft_strncmp(shell->command, *cmp,
					ft_strlen(shell->command)) == 0)
			{
				_free_command(&shell->command, *cmp);
				break ;
			}
			if (!shell->is_quoted_herdoc)
				*output = ft_joinstr(*output, get_real_command(shell, -1));
			else
				*output = ft_joinstr(*output, shell->command);
			free(*cmp);
			shell->command = get_next_line(0);
		}
	}
}

void	herdoc(t_shell *shell)
{
	int		i;
	char	*output;
	char	*cmp;

	i = -1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	output = ft_calloc(1, 1);
	if (shell->command)
	{
		free(shell->command);
		shell->command = 0;
	}
	read_herdoc(shell, &output, &cmp, &i);
	if (shell->command && !shell->command[0])
		free(shell->command);
	dup2(shell->herdoc[1], 1);
	close(shell->herdoc[0]);
	printf("%s", output);
	close(shell->herdoc[1]);
	free(output);
	exit(0);
}
