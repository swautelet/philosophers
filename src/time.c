/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:05:47 by swautele          #+#    #+#             */
/*   Updated: 2022/03/30 12:35:34 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

ssize_t	time_since(struct timeval last)
{
	struct timeval	now;
	ssize_t			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec - last.tv_sec) * 1000000;
	time += last.tv_usec;
	time -= now.tv_usec;
	time = time / 1000;
	return (time);
}

void	my_sleep(ssize_t time)
{
	int				i;
	struct timeval	now;

	i = 0;
	gettimeofday(&now, NULL);
	while (time_since(now) < time)
		i++;
}
