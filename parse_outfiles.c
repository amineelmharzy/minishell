/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:16:02 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/31 15:36:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_outfile(char *str)
{
	int		i;
	char	*outfile;

	while (*str != 0 && *str == ' ')
		str++;
	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '<' && str[i] != '>')
		i++;
	outfile = ft_calloc(i + 1, 1);
	if (!outfile)
		return (NULL);
	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		outfile[i] = str[i];
		i++;
	}
	outfile[i] = 0;
	return (outfile);
}

void	init_vars(int *var1, int *var2)
{
	*var1 = -1;
	*var2 = 0;
}

int	count_outfiles(char *str)
{
	int	i;
	int	count;

	init_vars(&i, &count);
	while (str[++i] != 0)
	{
		while (str[i] != 0 && str[i] == '\\' && str[i + 1] != 0)
			i += 2;
		if (str[i] == '>')
		{
			i++;
			while (str[i] != 0 && (str[i] == ' ' || str[i] == '<'
					|| str[i] == '\'' || str[i] == '\"' || str[i] == '>'))
				i++;
			if (str[i])
			{
				while (str[i] != 0 && str[i] != '<' && str[i] != '>'
					&& str[i] != ' ')
					i++;
				count++;
			}
			else
				return (-1);
		}
	}
	return (count);
}

int	parse_outfiles(t_shell *shell)
{
	char	*outfile;
	int		i;
	int		j;

	if (count_outfiles(shell->command) == -1)
		return (-1);
	else if (count_outfiles(shell->command) == 0)
		return (0);
	shell->outfiles = ft_calloc(count_outfiles(shell->command) + 1,
			sizeof(char *));
	if (!shell->outfiles)
		return (0);
	init_vars(&i, &j);
	while (shell->command[++i] != 0)
	{
		if (shell->command[i] == '<')
		{
			i++;
			outfile = get_outfile(&shell->command[i]);
			shell->outfiles[j++] = outfile;
		}
	}
	shell->outfiles[j] = 0;
	return (1);
}
