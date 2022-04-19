/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/04/19 14:40:58 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static void	l_to_rfork(t_param	*data)
{
	pthread_mutex_lock(data->lfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->lfork == data->rfork)
		return ;
	pthread_mutex_lock(data->rfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
}

static void	r_to_lfork(t_param	*data)
{
	pthread_mutex_lock(data->rfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->lfork == data->rfork)
		return ;
	pthread_mutex_lock(data->lfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
}

static void	philo_eat(t_param	*data)
{
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death
		&& data->numeal[0] != 0)
	{
		if (data->numeal[0] > 0)
			data->numeal[0]--;
		printf("%d	philo n° %d is eating\n", time_since(data->start),
			data->pos);
	}
	gettimeofday(&data->lastmeal, NULL);
	pthread_mutex_unlock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		my_sleep(data->eat);
	pthread_mutex_unlock(data->lfork);
	pthread_mutex_unlock(data->rfork);
}

static void	philo_sleep(t_param	*data)
{
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d is sleeping\n", time_since(data->start),
			data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		my_sleep(data->sleep);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d is thinking\n", time_since(data->start),
			data->pos);
	pthread_mutex_unlock(data->speachrod);
}

void	*philo_routine(void *info)
{
	t_param	*data;

	data = (t_param *)info;
	while (time_since(data->lastmeal) < data->death && data->flagdeath[0] == 0
		&& data->numeal[0] != 0)
	{
		if (data->pos % 2 == 0)
			l_to_rfork(data);
		else
			r_to_lfork(data);
		if (data->lfork == data->rfork)
			break ;
		philo_eat(data);
		philo_sleep(data);
	}
	if (data->lfork == data->rfork)
	{
		my_sleep(data->death);
		pthread_mutex_unlock(data->lfork);
	}
	philo_die(data);
	return (NULL);
}
