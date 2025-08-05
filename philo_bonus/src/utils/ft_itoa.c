/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:07:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:17:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static char	*ft_print_chars(char *ptr, int nbr, int count)
{
	while (nbr > 0)
	{
		ptr[count--] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (ptr);
}

static int	count_digits(int nbr)
{
	int	cmp;

	cmp = 0;
	if (nbr <= 0)
		cmp = 1;
	while (nbr != 0)
	{
		cmp++;
		nbr = nbr / 10;
	}
	return (cmp);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		nbr;
	int		count;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = count_digits(n);
	ptr = malloc(sizeof(char) * count + 1);
	if (!ptr)
		return (NULL);
	ptr[count--] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
	{
		nbr = n * -1;
		ptr[0] = '-';
	}
	else
		nbr = n;
	ptr = ft_print_chars(ptr, nbr, count);
	return (ptr);
}
