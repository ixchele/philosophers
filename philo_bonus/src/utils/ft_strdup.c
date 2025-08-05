/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:07:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:17:47 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

char	*ft_strdup(char *s1)
{
	int		i;
	char	*nv;
	size_t	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	nv = malloc(sizeof(char) * len + 1);
	if (!nv)
		return (NULL);
	while (s1[i])
	{
		nv[i] = s1[i];
		i++;
	}
	nv[i] = '\0';
	return (nv);
}
