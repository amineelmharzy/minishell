/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_iofiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:16:02 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 11:42:07 by ael-mhar         ###   ########.fr       */
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
	int	start;
	int	count;

	init_vars(&i, &count);
	start = 0;
	while (str[i] != 0)
	{
		while (str[i] == '\"' || str[i] == '\'')
		{
			start = str[i];
			i++;
			while (str[i] != 0 && str[i] != start)
				i++;
			i++;
		}
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
	int		start;
	int		i;
	int		j;

	init_vars(&i, &j);
	if (count_iofiles(shell->command, set) == 0)
		return (NULL);
	save = ft_calloc(1, 1);
	files = ft_calloc(1, 1);
	start = 0;
	while (shell->command[i] != 0)
	{
		while (shell->command[i] && (shell->command[i] == '\"' || shell->command[i] == '\"'))
		{
			start = shell->command[i];
			save = ft_joinchar(save, shell->command[i++]);
			while (shell->command[i] && shell->command[i] != start)
				save = ft_joinchar(save, shell->command[i++]);
			save = ft_joinchar(save, shell->command[i++]);
		}
		if (shell->command[i] && ft_strlen(&shell->command[i]) >= ft_strlen(set)
			&& !ft_strncmp(&shell->command[i], set, ft_strlen(set)))
		{
			i += ft_strlen(set);
			while (shell->command[i] != 0 && shell->command[i] == ' ')
				files = ft_joinchar(files, shell->command[i++]);
			start = shell->command[i];
			if (start == '\"' || start == '\'')
			{
				i++;
				while (shell->command[i] != 0 && shell->command[i] != '<'
					&& shell->command[i] != '>' && shell->command[i] != start)
					files = ft_joinchar(files, shell->command[i++]);
				i++;
			}
			else
			{
				while (shell->command[i] != 0 && shell->command[i] != '<'
					&& shell->command[i] != '>' && shell->command[i] != ' ')
					files = ft_joinchar(files, shell->command[i++]);
			}
			files = ft_joinchar(files, ' ');
		}
		else
			if (shell->command[i] != 0)
				save = ft_joinchar(save, shell->command[i++]);
	}
	free(shell->command);
	shell->command = save;
	return (files);
}

void	check_outfile(t_shell *shell)
{
	int	i;

	i = ft_strlen(shell->command) - 1;
	while (i >= 0)
	{
		if (shell->command[i] == '>' && i > 0 && shell->command[i - 1] == '>')
		{
			shell->ofile = 2;
			break;
		}
		if (shell->command[i] == '>')
		{
			shell->ofile = 1;
			break;
		}
		i--;
	}
}

int	implement_redirection(t_shell *shell)
{
	check_outfile(shell);
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
	/*
	int	i = 0;
	printf("------------- Herdocs -----------\n");
	if (shell->herdocs)
	{
		while (shell->herdocs[i])
			printf("%s\n", shell->herdocs[i++]);
	}
	i = 0;
	printf("\n------------- afiles -----------\n");
	if (shell->afiles)
	{
		while (shell->afiles[i])
			printf("%s\n", shell->afiles[i++]);
	}
	printf("\n------------- infiles -----------\n");
	i = 0;
	if (shell->infiles)
	{
		while (shell->infiles[i])
			printf("%s\n", shell->infiles[i++]);
	}
	i = 0;
	printf("\n------------- outfiles -----------\n");
	if (shell->outfiles)
	{
		while (shell->outfiles[i])
			printf("%s\n", shell->outfiles[i++]);
	}*/
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
