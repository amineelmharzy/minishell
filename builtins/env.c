/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:25:31 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/06 19:37:59 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*write_with_backslash(char *value)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	while (value[i] != 0)
	{
		if (value[i] == '\"' || value[i] == '$')
			res = ft_joinchar(res, '\\');
		res = ft_joinchar(res, value[i++]);
	}
	return (res);
}

void	print_env(t_env *temp, int option)
{
	char	*res;

	if (option == 0)
	{
		if (temp->value[0])
			printf("%s=%s\n", temp->key, temp->value);
		else if (temp->eq == 1)
			printf("%s=%s\n", temp->key, temp->value);
		return ;
	}
	if (temp->value[0])
	{
		res = write_with_backslash(temp->value);
		printf("declare -x %s=\"%s\"\n", temp->key, res);
		free(res);
	}
	else if (temp->eq == 1)
	{
		res = write_with_backslash(temp->value);
		printf("declare -x %s=\"%s\"\n", temp->key, res);
		free(res);
	}
	else
		printf("declare -x %s\n", temp->key);
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
	exit(0);
}
