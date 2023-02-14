/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:30:11 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/12 14:19:36 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*herdoc(t_shell *shell)
{
	int		i;
	char	*line;
	char	*output;

	i = -1;
	output = 0;
	while (shell->herdocs[++i] != 0)
	{
		line = readline("> ");
		if (output)
			free(output);
		output = ft_calloc(1, 1);
		while (line)
		{
			if (ft_strlen(line) == ft_strlen(shell->herdocs[i])
				&& ft_strncmp(line, shell->herdocs[i], ft_strlen(line)) == 0)
			{
				free(line);
				break ;
			}
			output = ft_joinstr(output, line);
			output = ft_joinchar(output, '\n');
			line = readline("> ");
		}
	}
	return (output);
}
