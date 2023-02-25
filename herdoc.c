/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:30:11 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/25 14:45:01 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_herdoc(t_shell *shell, char **output, int *i)
{
	while (shell->herdocs[++(*i)] != 0)
	{
		shell->command = readline("> ");
		if (*output)
			free(*output);
		*output = ft_calloc(1, 1);
		while (shell->command)
		{
			if (ft_strlen(shell->command) == ft_strlen(shell->herdocs[*i])
				&& ft_strncmp(shell->command, shell->herdocs[*i],
					ft_strlen(shell->command)) == 0)
			{
				free(shell->command);
				break ;
			}
			*output = ft_joinstr(*output, get_real_command(shell));
			*output = ft_joinchar(*output, '\n');
			shell->command = readline("> ");
		}
	}
}

char	*herdoc(t_shell *shell)
{
	int		i;
	char	*output;
	char	*save;

	i = -1;
	output = 0;
	save = ft_strdup(shell->command);
	read_herdoc(shell, &output, &i);
	shell->command = save;
	return (output);
}
