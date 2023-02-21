/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:43:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/20 20:21:56 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_node;

	shell->env = 0;
	shell->prompt = "~ ";
	shell->herdocs = 0;
	shell->infiles = 0;
	shell->afiles = 0;
	shell->outfiles = 0;
	shell->infile = 0;
	shell->outfile = 0;
	shell->exit_status = 0;
	shell->stdout_fd = dup(1);
	shell->stdin_fd = dup(0);
	shell->herdoc_output = 0;
	shell->envp = envp;
	shell->path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (shell->envp[i] != 0)
	{
		new_node = create_node(shell->envp[i]);
		insert_node_to_end(shell, new_node);
		i++;
	}
}
