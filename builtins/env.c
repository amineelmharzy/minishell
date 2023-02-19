/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:25:31 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 22:28:25 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

void	env(t_shell *shell, int opt)
{
	t_env	*temp;
	int		fd;

	fd = init_outfd(shell);
	temp = shell->env;
	dup2(fd, 1);
	while (temp)
	{
		if (opt == 0)
			if (temp->value[0])
				printf("%s=%s\n", temp->key, temp->value);
		else
		{
			if (temp->value[0])
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("declare -x %s\n", temp->key);
		}
		temp = temp->next;
	}
	if (fd != 1)
	{
		close(fd);
		dup2(shell->stdout_fd, 1);
	}
}
