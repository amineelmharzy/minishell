/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_iofiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:16:02 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/11 14:45:50 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*get_iofile(char *str)
{
	int		i;
	char	*iofile;

	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '<' && str[i] != '>')
		i++;
	iofile = ft_calloc(i + 1, 1);
	if (!iofile)
		return (NULL);
	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		iofile[i] = str[i];
		i++;
	}
	iofile[i] = 0;
	return (iofile);
}*/

void	init_vars(int *var1, int *var2)
{
	*var1 = 0;
	*var2 = 0;
}

int	count_iofiles(char *str, char *set)
{
	int	i;
	int	count;

	init_vars(&i, &count);
	while (str[i] != 0)
	{
		if (ft_strlen(&str[i]) >= ft_strlen(set) && ft_strncmp(&str[i], set,
				ft_strlen(set)) == 0)
		{
			i += ft_strlen(set);
			while (str[i] != 0 && str[i] == ' ')
				i++;
			if (str[i] == '<' || str[i] == '>')
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
		i++;
	}
	return (count);
}

/*
int	count_spaces(char *s)
{
	int	count;

	count = 0;
	while (*s != 0 && *s == ' ')
	{
		count++;
		s++;
	}
	return (count);
}
*/

int	check_error(t_shell *shell, char *set)
{
	if (count_iofiles(shell->command, set) == -1)
		return (1);
	return (0);
}

char	*parse_iofiles(t_shell *shell, char *set)
{
	char	*files;
	char	*save;
	int		i;
	int		j;

	init_vars(&i, &j);
	if (count_iofiles(shell->command, set) == 0)
		return (NULL);
	save = ft_calloc(1, 1);
	files = ft_calloc(1, 1);
	while (shell->command[i] != 0)
	{
		if (ft_strlen(&shell->command[i]) >= ft_strlen(set)
			&& !ft_strncmp(&shell->command[i], set, ft_strlen(set)))
		{
			i += ft_strlen(set);
			while (shell->command[i] != 0 && shell->command[i] == ' ')
				files = ft_joinchar(files, shell->command[i++]);
			while (shell->command[i] != 0 && shell->command[i] != '<'
				&& shell->command[i] != '>' && shell->command[i] != ' ')
				files = ft_joinchar(files, shell->command[i++]);
			files = ft_joinchar(files, ' ');
		}
		else
			save = ft_joinchar(save, shell->command[i++]);
	}
	shell->command = save;
	return (files);
}

int	implement_redirection(t_shell *shell)
{
	if (check_error(shell, "<<"))
	{
		printf("syntax error near unexpected token `newline' or `<<'\n");
		return (0);
	}
	shell->herdocs = ft_split(parse_iofiles(shell, "<<"), ' ');
	if (check_error(shell, ">>"))
	{
		printf("syntax error near unexpected token `newline' or `<<'\n");
		return (0);
	}
	shell->afiles = ft_split(parse_iofiles(shell, ">>"), ' ');
	if (check_error(shell, "<"))
	{
		printf("syntax error near unexpected token `newline' or `<<'\n");
		return (0);
	}
	shell->infiles = ft_split(parse_iofiles(shell, "<"), ' ');
	if (check_error(shell, ">"))
	{
		printf("syntax error near unexpected token `newline' or `<<'\n");
		return (0);
	}
	shell->outfiles = ft_split(parse_iofiles(shell, ">"), ' ');
	return (1);
}

/*
int main(int ac, char **av)
{
  t_shell shell;
  shell.command = ft_strdup(av[1]);
  char *arr;
  int	i = 0;
  printf("Herdocs\n----------------------------\n\n");
  arr = parse_iofiles(&shell, "<<");
  printf("%s\n", arr);
  //printf("%s\n", shell.command);
  printf("\nInfiles\n------------------------------\n\n");
  arr = parse_iofiles(&shell, "<");
  printf("%s\n", arr);
  printf("\nafiles\n------------------------------\n\n");
  arr = parse_iofiles(&shell, ">>");
  printf("%s\n", arr);
  //printf("%s\n", shell.command);
  printf("\nOutfiles\n------------------------------\n\n");
  arr = parse_iofiles(&shell, ">");
  printf("%s\n", arr);
  //printf("%s\n", shell.command);
}*/
