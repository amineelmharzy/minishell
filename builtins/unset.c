/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:27:46 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 11:30:14 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (shell->parsed_command[i] != 0)
	{
		j = 0;
		is_env(shell, shell->parsed_command[i],
			ft_strlen(shell->parsed_command[i]), 0);
		if (ft_strlen(shell->parsed_command[i]) == 4
			&& !ft_strncmp(shell->parsed_command[i], "PATH", 4))
		{
			if (shell->path)
			{
				while (shell->path[j] != 0)
					free(shell->path[j++]);
				free(shell->path);
				shell->path = ft_calloc(1, sizeof(char *));
			}
		}
		i++;
	}
	shell->exit_status = 0;
}
