/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:39:16 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 16:51:34 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node(char *var)
{
	char	**array;
	t_env	*node;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	i = 1;
	array = ft_split(var, '=');
	node->key = ft_strdup(array[0]);
	node->value = ft_calloc(1, 1);
	free(array[0]);
	while (array[i])
	{
		node->value = ft_joinstr(node->value, ft_strdup(array[i]));
		free(array[i]);
		i++;
	}
	node->next = 0;
	free(array);
	return (node);
}

void	insert_node_to_end(t_shell *shell, t_env *new_node)
{
	t_env	*lst;

	lst = shell->env;
	if (!(shell->env) && new_node)
	{
		shell->env = new_node;
		return ;
	}
	else if (!(shell->env) || !new_node)
	{
		return ;
	}
	while ((shell->env)->next)
	{
		(shell->env) = (shell->env)->next;
	}
	(shell->env)->next = new_node;
	shell->env = lst;
}

void	init_env(t_shell *shell)
{
	int		i;
	t_env	*new_node;
	shell->env = 0;
	i = 0;
	while (shell->envp[i] != 0)
	{
		new_node = create_node(shell->envp[i]);
		insert_node_to_end(shell, new_node);
		i++;
	}
}

void	add_env_var(t_shell *shell, char *var)
{
	t_env	*node;

	node = create_node(var);
	insert_node_to_end(shell, node);
}

char	*is_env(t_shell *shell, char *s, int n, int ret)
{
	t_env	*env;
	t_env	*tmp1;
	t_env	*tmp2;

	env = shell->env;
	while (env)
	{
		if (ft_strlen(env->key) == n)
		{
			if (ft_strncmp(env->key, s, n) == 0)
			{
				if (ret == 0)
				{
					tmp2 = env->next;
					free(env->key);
					free(env->value);
					free(env);
					tmp1->next = tmp2;
					env = tmp2;
					return (NULL);
				}
				else
					return (env->value);
			}
		}
		tmp1 = env;
		env = env->next;
	}
	return (NULL);
}

void	free_all(t_shell *shell, int option)
{
	t_env	*env;
	t_env	*temp;
	int		i;

	env = shell->env;
	i = 0;
	if (shell->infiles)
	{
		while (shell->infiles[i])
			free(shell->infiles[i++]);
		free(shell->infiles);
		shell->infiles = 0;
	}
	if (shell->herdocs)
	{
		while (shell->herdocs[i])
			free(shell->herdocs[i++]);
		free(shell->herdocs);
		shell->herdocs = 0;
	}
	if (shell->afiles)
	{
		while (shell->afiles[i])
			free(shell->afiles[i++]);
		free(shell->afiles);
		shell->afiles = 0;
	}
	if (shell->outfiles)
	{
		while (shell->outfiles[i])
			free(shell->outfiles[i++]);
		free(shell->outfiles);
		shell->outfiles = 0;
	}
	if (shell->commands)
	{
		free(shell->commands);
		shell->commands = 0;
	}
	if (option == 1)
	{
		while (shell->path[i] != 0)
			free(shell->path[i++]);
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

/*
void	del_env_var(t_shell *shell, char *var)
{
	t_env	*temp;

	if (ft_strlen(shell->env->key) == ft_strlen(var))
	{
		if (strncmp(shell->env->key, var, ft_strlen(var)) == 0)
		{
			free(shell->env);
			shell->env = shell->env->next;
		}
	}
}
*/
