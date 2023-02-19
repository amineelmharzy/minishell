/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:17:17 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 23:31:40 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_shell *shell)
{
	char	*target_dir;

	if (!shell->real_command[1])
		target_dir = getenv("HOME");
	else
		target_dir = shell->real_command[1];
	if (shell->real_command[1] && shell->real_command[2])
	{
		print_error(shell, shell->real_command[0], E_TOMR);
		shell->exit_status = 1;
		return ;
	}
	if (chdir(target_dir) != 0)
	{
		perror("Minishell ");
		shell->exit_status = 1;
	}
}
