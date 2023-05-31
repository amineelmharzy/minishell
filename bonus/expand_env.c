/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:25:41 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/31 15:14:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_all_ws(char **res, char *s, int op)
{
	int	i;
	int	len;

	i = 0;
	while (!op && s[i] && (s[i] == ' ' || s[i] == '\t'))
	{
		*res = ft_joinchar(*res, ' ');
		i++;
	}
	if (!op && !s[i])
		return (1);
	len = ft_strlen(s) - 1;
	if (op && (s[len] == ' ' || s[len] == '\t'))
		*res = ft_joinchar(*res, ' ');
	return (0);
}

char	*__funcl(char *str)
{
	char	**arr;
	char	*res;
	char	*s;
	int		i;

	i = 0;
	res = ft_calloc(1, 1);
	if (check_all_ws(&res, str, 0))
		return (res);
	arr = ft_split(str, ' ');
	while (arr[i])
	{
		if (ft_strchr(arr[i], '*'))
		{
			s = &arr[i][0];
			res = ft_joinstr(res, expand_astric(&arr[i++]));
			free(s);
		}
		else
			res = ft_joinstr(res, arr[i++]);
		if (arr[i])
			res = ft_joinchar(res, ' ');
	}
	check_all_ws(&res, str, 1);
	return (free(arr), res);
}

int	expand_env(t_shell *shell, char *str, char **real)
{
	int		i;
	char	*env;
	char	*s;

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
		*real = ft_joinstr(*real, __funcl(env));
	return (i);
}
