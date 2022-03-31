/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:05:47 by swautele          #+#    #+#             */
/*   Updated: 2022/03/31 15:27:53 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	time_since(struct timeval last)
{
	struct timeval	now;
	int				time;

	gettimeofday(&now, NULL);
	if (now.tv_sec != last.tv_sec)
	{
		time = (now.tv_sec - last.tv_sec) * 1000000;
		time -= last.tv_usec;
		time += now.tv_usec;
	}
	else
	{
		time = now.tv_usec;
		time -= last.tv_usec;
	}
	time = time / 1000;
	// printf("now.tvsec = %zd	now.tvusec = %d		last.tvsec = %zd last.tvusec = %d\n", now.tv_sec, now.tv_usec, last.tv_sec, last.tv_usec);
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
