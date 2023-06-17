/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:56:36 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 11:34:58 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_infiles(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->infiles)
	{
		while (shell->infiles[i])
			free(shell->infiles[i++]);
		free(shell->infiles);
		shell->infiles = 0;
		shell->infile = 0;
	}
	if (shell->herdocs)
	{
		i = 0;
		while (shell->herdocs[i])
			free(shell->herdocs[i++]);
		free(shell->herdocs);
		shell->herdocs = 0;
	}
	shell->is_infile = 0;
	shell->is_herdoc = 0;
}

void	free_outfiles(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->afiles)
	{
		while (shell->afiles[i])
			free(shell->afiles[i++]);
		free(shell->afiles);
		shell->afiles = 0;
	}
	if (shell->outfiles)
	{
		i = 0;
		while (shell->outfiles[i])
			free(shell->outfiles[i++]);
		free(shell->outfiles);
		shell->outfiles = 0;
	}
	shell->outfile = 0;
	free_infiles(shell);
}

void	free_commands(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->commands)
	{
		while (shell->commands[i] != 0)
			free(shell->commands[i++]);
		free(shell->commands);
		shell->commands = 0;
	}
	shell->is_builtin = 0;
	shell->is_pipe = 0;
}

void	free_command(t_shell *shell, int i)
{
	i = 0;
	if (shell->parsed_command)
	{
		while (shell->parsed_command[i] != 0)
			free(shell->parsed_command[i++]);
		free(shell->parsed_command);
		shell->parsed_command = 0;
		i = 0;
	}
}

void	free_all(t_shell *shell, int option)
{
	t_env	*env;
	t_env	*temp;
	int		i;

	i = 0;
	env = shell->env;
	free_outfiles(shell);
	free_command(shell, 0);
	if (option == 0)
		free_commands(shell);
	if (option == 1)
	{
		while (shell->path && shell->path[i] != 0)
			free(shell->path[i++]);
		if (shell->path)
			free(shell->path);
		while (env)
		{
			temp = env->next;
			free(env->key);
			free(env->value);
			free(env);
			env = temp;
		}
	}
}
