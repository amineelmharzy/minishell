/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file_with_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:49:21 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/29 16:49:25 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_fine_with_quotes(char *command)
{
	int	i;
	int	end;
	int	start;

	i = 0;
	end = 0;
	start = 0;
	while (command[i] != 0)
	{
		if (end != 0)
			return (-1);
		while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
			i++;
		if (command[i] == '\\' && (command[i + 1] == '\'' || command[i
				+ 1] == '\"'))
			i += 2;
		if (command[i] == '\"' || command[i] == '\'')
		{
			start = command[i];
			i++;
			while (command[i] != 0 && command[i] != start)
				i++;
			if (command[i] == start)
				end = 0;
			else
			{
				end = 1;
				i++;
			}
		}
		i++;
	}
	if (end == 0)
		return (0);
	return (-1);
}
