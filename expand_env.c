/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:25:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 10:25:49 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_env(t_shell *shell, char *str, char **real)
{
	int		i;
	char	*env;

	i = 0;
	if (str[0] && str[0] == '?')
	{
		*real = ft_joinstr(*real, ft_itoa(shell->exit_status));
		return (1);
	}
	while (str[i] != 0)
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	env = is_env(shell, str, i, 1);
	if (env)
		*real = ft_joinstr(*real, ft_strdup(env));
	return (i);
}
