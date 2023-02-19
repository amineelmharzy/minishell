/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:14:38 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 22:49:29 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_shell *shell)
{
	int		i;
	char	*key;

	if (!(shell->real_command[1]))
	{
		env(shell, 1);
		return ;
	}
	i = 0;
	while (shell->real_command[++i] != 0)
	{
		if (!check_identifier(shell, shell->real_command[i]))
		{
			key = exported_key(shell->real_command[i]);
			if (ft_strchr(shell->real_command[i], '='))
			{
				is_env(shell, key, ft_strlen(key), 0);
				add_env_var(shell, shell->real_command[i]);
			}
			else
				if (!is_env(shell, key, ft_strlen(key), 1))
					add_env_var(shell, shell->real_command[i]);
			free(key);
		}
	}
}
