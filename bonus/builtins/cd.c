/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:17:17 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/28 09:35:18 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_shell *shell)
{
	char	*target_dir;

	if (!shell->parsed_command[1])
		target_dir = is_env(shell, "HOME", 4, 1);
	else
		target_dir = shell->parsed_command[1];
	if (!target_dir)
	{
		print_error(shell, shell->parsed_command[0], E_NOHS, 1);
		return ;
	}
	if (shell->parsed_command[1] && shell->parsed_command[2])
	{
		print_error(shell, shell->parsed_command[0], E_TOMR, 1);
		return ;
	}
	if (chdir(target_dir) != 0)
	{
		perror("minishell");
		shell->exit_status = 1;
	}
	else
	{
		shell->exit_status = 0;
		is_env(shell, "PWD", 3, 0);
		getcwd(shell->cwd, sizeof(shell->cwd));
		target_dir = ft_strjoin("PWD=", shell->cwd);
		add_env_var(shell, target_dir, 0);
		free(target_dir);
	}
}
