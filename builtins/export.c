/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:14:38 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/22 10:14:47 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_shell *shell)
{
	int		i;
	char	*key;

	if (!(shell->parsed_command[1]))
	{
		run_env(shell, 1, env);
		return ;
	}
	i = 0;
	while (shell->parsed_command[++i] != 0)
	{
		if (!check_identifier(shell, shell->parsed_command[i]))
		{
			key = exported_key(shell->parsed_command[i]);
			if (ft_strchr(shell->parsed_command[i], '='))
			{
				is_env(shell, key, ft_strlen(key), 0);
				add_env_var(shell, shell->parsed_command[i]);
			}
			else
				if (!is_env(shell, key, ft_strlen(key), 1))
					add_env_var(shell, shell->parsed_command[i]);
			free(key);
		}
	}
}
