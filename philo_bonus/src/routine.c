/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/04/30 15:09:02 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static int	take_fork(t_param	*data)
{
	if ((data->eat >= data->death && data->pos % 2 == 1))
		return (-1);
	if (data->death - time_since(data->lastmeal) < data->eat && data->eat * 2
		> data->death)
	{
		while (my_sleep(1, data) != -1)
			;
		return (-1);
	}
	sem_wait(data->forks);
	sem_wait(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d has taken a fork\n",
			time_since(data->start), data->pos);
	sem_post(data->speachrod);
	if (data->number == 1)
		return (-1);
	sem_wait(data->forks);
	sem_wait(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d has taken a fork\n",
			time_since(data->start), data->pos);
	sem_post(data->speachrod);
	return (0);
}

static int	philo_eat(t_param	*data)
{
	int	check;

	check = 0;
	sem_wait(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death
		&& data->meal != 0)
	{
		if (data->meal > 0)
			data->meal--;
		printf("%d	%d is eating\n", time_since(data->start),
			data->pos);
		if (data->meal == 0)
			check = 1;
		gettimeofday(&data->lastmeal, NULL);
	}
	sem_post(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		if (my_sleep(data->eat, data) == -1)
			check = -1;
	sem_post(data->forks);
	sem_post(data->forks);
	return (check);
}

static int	philo_sleep(t_param	*data)
{
	sem_wait(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d is sleeping\n", time_since(data->start),
			data->pos);
	sem_post(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		if (my_sleep(data->sleep, data) == -1)
			return (-1);
	sem_wait(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d is thinking\n", time_since(data->start),
			data->pos);
	sem_post(data->speachrod);
	return (0);
}

void	*philo_routine(void *info)
{
	t_param	*data;

	data = (t_param *)info;
	if (data->pos % 2 == 0)
		my_sleep(data->eat / 2, data);
	while (time_since(data->lastmeal) < data->death && data->flagdeath[0] == 0
		&& data->meal != 0)
	{
		if (take_fork(data) == -1)
			break ;
		if (data->number == 1)
			break ;
		if (philo_eat(data) != 0)
			break ;
		if (philo_sleep(data) != 0)
			break ;
	}
	if (data->number == 1)
		while (my_sleep(1, data) != -1)
			;
	philo_die(data);
	return (NULL);
}
