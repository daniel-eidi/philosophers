/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:10:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/10 17:31:39 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
/**
 * @brief convert to int.
 * 
 * @param str 
 * @return long 
 */

int	ft_atoi(const char *str)
{
	unsigned long	nbr;
	unsigned long	sign;
	unsigned int	i;

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
	return ((int)(nbr * sign));
}
