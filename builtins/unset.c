/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:27:46 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/22 11:19:16 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->parsed_command[i] != 0)
	{
		is_env(shell, shell->parsed_command[i],
			ft_strlen(shell->parsed_command[i]), 0);
		i++;
	}
}
