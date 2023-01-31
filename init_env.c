/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:39:16 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/31 11:30:51 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node(char *var)
{
	t_env	*node;
	char	**env_var;

	node = malloc(sizeof(t_env *));
	env_var = ft_split(var, '=');
	if (!node)
		return (0);
	node->key = env_var[0];
	node->value = env_var[1];
	node->next = NULL;
	return (node);
}

void	insert_node_to_end(t_env **head, t_env *new_node)
{
	t_env	*lst;

	lst = *head;
	if (!(*head) && new_node)
	{
		*head = new_node;
		return ;
	}
	else if (!(*head) || !new_node)
	{
		return ;
	}
	while ((*head)->next)
	{
		(*head) = (*head)->next;
	}
	(*head)->next = new_node;
	*head = lst;
}

void	init_env(t_shell *shell)
{
	int		i;
	t_env	*new_node;
	t_env	*head;

	i = 0;
	head = NULL;
	while (shell->envp[i] != 0)
	{
		new_node = create_node(shell->envp[i]);
		insert_node_to_end(&head, new_node);
		i++;
	}
	shell->env = head;
}

void	add_env_var(t_shell *shell, char *var)
{
	t_env	*node;

	node = create_node(var);
	insert_node_to_end(&shell->env, node);
}

char	*is_env(t_shell *shell, char *s, int n)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strlen(env->key) == n)
		{
			if (ft_strncmp(env->key, s, n) == 0)
				return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void	free_env(t_shell *shell)
{
	t_env	*env;
	t_env	*temp;

	env = shell->env;
	while (env)
	{
		free(env->key);
		free(env->value);
		temp = env;
		free(env);
		env = temp->next;
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
