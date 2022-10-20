/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:10:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/20 19:14:12 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
/**
 * @brief convert to int.
 * 
 * @param str 
 * @return long 
 */

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long long	ft_atol(const char *str)
{
	unsigned long long		nbr;
	unsigned long		sign;
	unsigned long		i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' \
	|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit((int) str[i]))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return ((long long)(nbr * sign));
}
