/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:43:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/12 18:23:04 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_variables(t_shell *shell, char **envp)
{
	shell->env = 0;
	shell->prompt = 0;
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
	if (getenv("PATH") == NULL)
		shell->path = ft_split("/usr/local/bin:/bin:/usr/bin", ':');
	else
		shell->path = ft_split(getenv("PATH"), ':');
	shell->is_pipe = 0;
	shell->is_builtin = 0;
	shell->fcommands = 0;
	shell->or_commands = 0;
	shell->s_iofiles = 0;
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
