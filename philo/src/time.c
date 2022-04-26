/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:05:47 by swautele          #+#    #+#             */
/*   Updated: 2022/04/26 16:45:47 by swautele         ###   ########.fr       */
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

void	philo_die(t_param	*data)
{
	if (data->eat >= data->death)
		my_sleep(data->death + 1, data);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] <= 0 && data->meal != 0
		&& time_since(data->lastmeal) > data->death)
	{
		data->flagdeath[0] = 1;
		printf("%d	%d died\n", time_since(data->start), data->pos);
	}
	else
		data->flagdeath[0]--;
	pthread_mutex_unlock(data->speachrod);
}

void	check_death(t_param	*info)
{
	int	i;

	i = -1;
	while (++i < info->number)
	{
		pthread_mutex_lock(info->speachrod);
		if (time_since((info + i)->lastmeal) > info->death)
		{
			info->flagdeath[0]++;
			printf("%d	%d died\n", time_since(info->start), i);
			pthread_mutex_unlock(info->speachrod);
			return ;
		}
		pthread_mutex_unlock(info->speachrod);
		if (i == info->number - 1)
			i = -1;
		pthread_mutex_lock(info->speachrod);
		if (info->flagdeath[0] == -info->number)
			return ;
		pthread_mutex_unlock(info->speachrod);
	}
}
