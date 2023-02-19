/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:27:46 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 23:34:20 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->real_command[i] != 0)
	{
		is_env(shell, shell->real_command[i],
			ft_strlen(shell->real_command[i]), 0);
		i++;
	}
}
