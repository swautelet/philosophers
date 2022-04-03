/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:05:47 by swautele          #+#    #+#             */
/*   Updated: 2022/04/04 01:49:54 by simonwautel      ###   ########.fr       */
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

void	my_sleep(int time)
{
	// int				i;
	// int				j;
	struct timeval	now;
	// (void)start;

	gettimeofday(&now, NULL);
	// j = time_since(start);
	// if (time > 0)
		// i = ((time * 1000) - 5000);
	// else
		// i = 0;
	// if (i > 0)
		// usleep(i);
	while (time_since(now) < time)
	{
		// i++;
		usleep(900);
	}
}
