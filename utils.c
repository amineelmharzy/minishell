/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:39:16 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 17:37:53 by ael-mhar         ###   ########.fr       */
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

void	add_env_var(t_shell *shell, char *var)
{
	t_env	*node;

	node = create_node(var);
	insert_node_to_end(shell, node);
}

void	free_env(t_env **tmp1, t_env **tmp2, t_env *env)
{
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
	while (env)
	{
		if (ft_strlen(env->key) == n)
		{
			if (ft_strncmp(env->key, s, n) == 0)
			{
				if (ret == 0)
				{
					free_env(&tmp1, &tmp2, env);
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
