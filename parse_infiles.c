/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:16:02 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/08 10:43:54 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_infile(char *str)
{
	int		i;
	char	*infile;

	while (*str != 0 && *str == ' ')
		str++;
	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '<' && str[i] != '>')
		i++;
	infile = ft_calloc(i + 1, 1);
	if (!infile)
		return (NULL);
	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		infile[i] = str[i];
		i++;
	}
	infile[i] = 0;
	return (infile);
}

void	init_vars(int *var1, int *var2)
{
	*var1 = -1;
	*var2 = 0;
}

int	count_infiles(char *str)
{
	int	i;
	int	count;

	init_vars(&i, &count);
	while (str[++i] != 0)
	{
		while (str[i] != 0 && str[i] == '\\' && str[i + 1] != 0)
			i += 2;
		if (str[i] == '<')
		{
			i++;
			while (str[i] != 0 && str[i] == ' ')
				i++;
			if (str[i] && (str[i] == '>' || str[i] == '<'))
				return (-1);
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

int	parse_infiles(t_shell *shell)
{
	char	*infile;
	int		i;
	int		j;

	if (count_infiles(shell->command) == -1)
	{
		printf("error\n");
		exit(0);
		return (-1);
	}
	else if (count_infiles(shell->command) == 0)
		return (0);
	shell->infiles = ft_calloc(count_infiles(shell->command) + 1,
			sizeof(char *));
	if (!shell->infiles)
		return (0);
	init_vars(&i, &j);
	while (shell->command[++i] != 0)
	{
		if (shell->command[i] == '<')
		{
			i++;
			infile = get_infile(&shell->command[i]);
			shell->infiles[j++] = infile;
		}
	}
	shell->infiles[j] = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_shell	shell;

	int i = 0;
	shell.command = ft_strdup(av[1]);
	if (parse_infiles(&shell) == 0)
		return (0);
	while (shell.infiles[i])
	{
		printf("%s\n", shell.infiles[i]);
		i++;
	}
	return (0);
}
