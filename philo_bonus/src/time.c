/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:05:47 by swautele          #+#    #+#             */
/*   Updated: 2022/04/27 15:08:10 by swautele         ###   ########.fr       */
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
	return (time);
}

int	my_sleep(int time, t_param *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (time_since(now) < time)
	{
		if (time_since(data->lastmeal) > data->death)
			return (-1);
		usleep(900);
	}
	return (0);
}

int	philo_die(t_param	*data)
{
	if (data->number == 1)
	{
		my_sleep(data->death, data);
		sem_post(data->forks);
	}
	if (data->eat >= data->death)
		my_sleep(data->death, data);
	if (data->flagdeath[0] == 0 && data->meal != 0
		&& time_since(data->lastmeal) > data->death)
	{
		sem_wait(data->speachrod);
		data->flagdeath[0]++;
		printf("%d	%d died\n", time_since(data->start), data->pos);
		exit (1);
	}
	exit (0);
}
