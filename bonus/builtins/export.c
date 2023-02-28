/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:14:38 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/26 11:43:21 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_variables2(t_shell *shell, int *i)
{
	shell->exit_status = 0;
	*i = 0;
}

void	export(t_shell *shell)
{
	int		i;
	char	*key;

	if (!(shell->parsed_command[1]))
	{
		run_env(shell, 1, env);
		return ;
	}
	init_variables2(shell, &i);
	while (shell->parsed_command[++i] != 0)
	{
		if (!check_identifier(shell, shell->parsed_command[i]))
		{
			key = exported_key(shell->parsed_command[i]);
			if (ft_strchr(shell->parsed_command[i], '='))
			{
				is_env(shell, key, ft_strlen(key), 0);
				add_env_var(shell, shell->parsed_command[i], 1);
			}
			else
				if (!is_env(shell, key, ft_strlen(key), 1))
					add_env_var(shell, shell->parsed_command[i], 0);
			free(key);
		}
	}
}
