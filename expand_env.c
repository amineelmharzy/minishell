/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:25:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/11 19:29:29 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	over_with_dquotes(char **real, char *env)
{
	int	i;

	i = 0;
	if (env[0] == '\'')
		*real = ft_joinchar(*real, '\"');
	while (env[i] != 0)
		*real = ft_joinchar(*real, env[i++]);
	if (env[ft_strlen(env) - 1] == '\'')
		*real = ft_joinchar(*real, '\"');
}

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
	if (str[i] == '@' || (str[i] >= '0' && str[i] <= '9'))
		return (i + 1);
	while (str[i] != 0)
	{
		if (!ft_isalnum(str[i]) || str[i] == '$' || str[i] == ' ')
			break ;
		i++;
	}
	env = is_env(shell, str, i, 1);
	if (env)
		over_with_dquotes(real, env);
	return (i);
}
