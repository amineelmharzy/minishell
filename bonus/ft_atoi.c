/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:49:18 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/06 09:56:30 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_errs(t_shell *shell, char *str, char *str2, int i)
{
	char	*err;

	if (str[i] != 0)
	{
		err = ft_strjoin("exit: ", str);
		print_error(shell, err, "numeric argument required", 255);
		free(err);
		return (255);
	}
	if (str2)
	{
		print_error(shell, "exit", "too many arguments", 1);
		return (-1);
	}
	return (0);
}

int	ft_atoi(t_shell *shell, char *str, char *str2)
{
	int			is_negative;
	int			i;
	long long	number;

	is_negative = 1;
	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative = is_negative * (-1);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	i = exit_errs(shell, str, str2, i);
	if (i != 0)
		return (i);
	if (number * is_negative == -1)
		return (255);
	return (number * is_negative);
}
