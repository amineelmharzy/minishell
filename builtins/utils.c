/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:06:56 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 12:35:02 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_outfd(t_shell *shell)
{
	int	fd;

	fd = 1;
	if (shell->outfile)
	{
		if (shell->ofile == 1)
			fd = open(shell->outfile, O_TRUNC | O_WRONLY);
		else
			fd = open(shell->outfile, O_WRONLY | O_APPEND);
	}
	if (fd == 1 && shell->is_pipe)
		fd = 0;
	return (fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	len;

	if (!s || !fd)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		write(fd, &s[i], fd);
		i++;
	}
}

char	*exported_key(char *var)
{
	int		i;
	char	*key;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = ft_calloc(i + 1, 1);
	if (!key)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		key[i] = var[i];
		i++;
	}
	key[i] = 0;
	return (key);
}

int	check_identifier(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] < 65 || (str[i] < 97 && str[i] > 90 && str[i] != 95)
		|| str[i] > 122)
	{
		write(2, "Minishell : not a valid identifier\n", 36);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}
