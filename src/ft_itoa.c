/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/20 08:55:50 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	ft_numdec(unsigned int i)
{
	unsigned int	count;

	count = 1;
	while (i > 9)
	{
		i = i / 10;
		count ++;
	}
	return (count);
}

/**
 * @brief Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 * 
 * @param n 
 * @return char* 
 */
char	*ft_itoa(long n)
{
	char			*str;
	int				len;
	unsigned long	ncp;

	len = ft_numdec(n);
	ncp = n;
	if (n < 0)
		len = ft_numdec(-ncp) + 1;
	str = (char *) ft_calloc(1, len + 1);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		ncp = -n;
	}
	str[len] = '\0';
	while (ncp > 9)
	{
		str[len - 1] = ncp % 10 + '0';
		ncp = ncp / 10;
		len--;
	}
	str[len - 1] = ncp % 10 + '0';
	return (str);
}

// void	ft_print_result(char const *s)
// {
// 	int		len;

// 	len = 0;
// 	while (s[len])
// 		len++;
// 	write(1, s, len);
// }

// int main()
// {
// 	ft_print_result(ft_itoa(-2147483648));
// 	return (0);
// }
