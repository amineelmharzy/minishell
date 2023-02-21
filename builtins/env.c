/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:25:31 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/20 19:16:36 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *temp, int option)
{
	if (option == 0)
	{
		if (temp->value[0])
			printf("%s=%s\n", temp->key, temp->value);
	}
	else if (option == 1)
	{
		if (temp->value[0])
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
	}
}

void	env(t_shell *shell, int opt)
{
	t_env	*temp;
	int		fd;

	fd = init_outfd(shell);
	temp = shell->env;
	if (fd != 1)
		dup2(fd, 1);
	while (temp)
	{
		if (opt == 0)
			print_env(temp, 0);
		else
			print_env(temp, 1);
		temp = temp->next;
	}
	if (fd != 1)
	{
		close(fd);
		dup2(shell->stdout_fd, 1);
	}
}
