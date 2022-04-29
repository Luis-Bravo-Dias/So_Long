/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:10:32 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 17:15:47 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

size_t	ft_strlen(const char	*str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
		n++;
	return (n);
}

static int	ft_nlen(long int i)
{
	int	count;

	count = 0;
	if (i < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

char	*ft_transform(long int nb, char *s, int len)
{
	if (nb < 0)
	{
		s[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		s[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			len;
	long int	nb;
	char		*s2;

	nb = n;
	if (nb == 0)
	{
		return (ft_strdup("0"));
	}
	len = ft_nlen(nb);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len--] = 0;
	s2 = ft_transform(nb, s, len);
	return (s2);
}
