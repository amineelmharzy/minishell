/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:43:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/05 15:58:50 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_variables(t_shell *shell, char **envp)
{
	shell->env = 0;
	shell->herdocs = 0;
	shell->infiles = 0;
	shell->afiles = 0;
	shell->outfiles = 0;
	shell->parsed_command = 0;
	shell->commands = 0;
	shell->infile = 0;
	shell->outfile = 0;
	shell->exit_status = 0;
	shell->stdout_fd = dup(1);
	shell->stdin_fd = dup(0);
	shell->herdoc_output = 0;
	shell->is_herdoc = 0;
	shell->envp = envp;
	shell->path = 0;
	shell->path = ft_split(getenv("PATH"), ':');
	shell->is_pipe = 0;
	shell->is_builtin = 0;
	shell->quoted_afiles = 0;
	shell->quoted_outfiles = 0;
}

void	init_shell(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_node;

	init_shell_variables(shell, envp);
	i = 0;
	while (shell->envp[i] != 0)
	{
		new_node = create_node(shell->envp[i], 0);
		insert_node_to_end(shell, new_node);
		i++;
	}
}
