/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fine_with_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:49:21 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/16 16:58:37 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	discard_quotes(char *str, int *i, int *end)
{
	int	start;

	start = 0;
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		start = str[*i];
		(*i)++;
		while (str[*i] != 0 && str[*i] != start)
			(*i)++;
		if (str[*i] == start)
			*end = 0;
		else
		{
			*end = 1;
			(*i)++;
		}
	}
}

int	is_fine_with_quotes(char *command)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (command[i] != 0)
	{
		if (end != 0)
			return (-1);
		while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
			i++;
		if (command[i] == '\\' && (command[i + 1] == '\'' || command[i
					+ 1] == '\"'))
			i += 2;
		discard_quotes(command, &i, &end);
		i++;
	}
	if (end == 0)
		return (0);
	return (-1);
}
