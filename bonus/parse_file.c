/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:21:43 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/06 15:01:36 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_file(t_shell *shell, char **files, char *set, int *i)
{
	char	*str;
	int		start;

	str = shell->command;
	start = str[*i];
	if (start == '\"' || start == '\'')
	{
		if (set[0] == '<' && str[1] == '<')
			shell->is_quoted_herdoc = 1;
		*files = ft_joinchar(*files, str[(*i)++]);
		while (str[*i] != 0 && str[*i] != start)
			*files = ft_joinchar(*files, str[(*i)++]);
		*files = ft_joinchar(*files, str[(*i)++]);
	}
	else
	{
		shell->is_quoted_herdoc = 0;
		*files = ft_joinchar(*files, str[(*i)++]);
	}
}
