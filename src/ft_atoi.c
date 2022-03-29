/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:38:37 by swautele          #+#    #+#             */
/*   Updated: 2022/03/29 14:32:04 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static int	ft_sign(const char *str)
{
	int	s;

	s = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			s = s * (-1);
		}
		str++;
	}
	return (s);
}

int	ft_atoi(const char *str, char *flagerr)
{
	int		s;
	size_t	nb;

	nb = 0;
	s = ft_sign(str);
	if (*str == '+' || *str == '-')
		str++;
	if (*str < 48 || *str > 57)
		*flagerr = -1;
	while (*str >= 48 && *str <= 57)
	{
		nb = nb * 10 + (*str - 48);
		str++;
		if ((s == -1 && nb > 2147483648) || (s == 1 && nb > 2147483647))
			*flagerr = -1;
	}
	if ((*str < 48 || *str > 57) & *str)
		*flagerr = -1;
	if ((s == -1 && nb > 2147483648) || (s == 1 && nb > 2147483647))
	{
		*flagerr = -1;
		return (0);
	}
	return (nb * s);
}
