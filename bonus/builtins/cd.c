/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:17:17 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 11:29:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_set_cwd(t_shell *shell, char **target_dir)
{
	shell->exit_status = 0;
	is_env(shell, "PWD", 3, 0);
	getcwd(shell->cwd, sizeof(shell->cwd));
	*target_dir = ft_strjoin("PWD=", shell->cwd);
	add_env_var(shell, *target_dir, 0);
	free(*target_dir);
}

void	cd(t_shell *shell)
{
	char	*target_dir;

	if (!shell->parsed_command[1])
		target_dir = is_env(shell, "HOME", 4, 1);
	else
		target_dir = shell->parsed_command[1];
	if (!target_dir)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		shell->exit_status = 1;
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
		_set_cwd(shell, &target_dir);
}
