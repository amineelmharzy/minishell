/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:39:16 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/04/16 18:21:51 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node(char *var, int op)
{
	char	**array;
	t_env	*node;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	array = ft_split(var, '=');
	node->key = ft_strdup(array[0]);
	node->value = ft_calloc(1, 1);
	free(array[0]);
	if (!array[1] && !op)
		node->eq = 1;
	i = 0;
	while (array[++i])
	{
		if (array[i + 1])
			node->value = ft_joinstr(node->value, ft_strjoin(array[i], "="));
		else
			node->value = ft_joinstr(node->value, ft_strdup(array[i]));
		free(array[i]);
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

void	add_env_var(t_shell *shell, char *var, int op)
{
	t_env	*node;

	node = create_node(var, 1);
	if (op == 1)
		node->eq = 1;
	insert_node_to_end(shell, node);
}

void	free_env(t_shell *shell, t_env **tmp1, t_env **tmp2, t_env *env)
{
	if (*tmp1 == env)
	{
		shell->env = shell->env->next;
		free(env->key);
		free(env->value);
		free(env);
		return ;
	}
	*tmp2 = env->next;
	free(env->key);
	free(env->value);
	free(env);
	(*tmp1)->next = *tmp2;
	env = *tmp2;
}

char	*is_env(t_shell *shell, char *s, int n, int ret)
{
	t_env	*env;
	t_env	*tmp1;
	t_env	*tmp2;

	env = shell->env;
	tmp1 = env;
	while (env)
	{
		if (ft_strlen(env->key) == n)
		{
			if (ft_strncmp(env->key, s, n) == 0)
			{
				if (ret == 0)
				{
					free_env(shell, &tmp1, &tmp2, env);
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
