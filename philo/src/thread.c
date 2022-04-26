/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/26 16:33:31 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo(t_param *param, t_param *info, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < param->number)
	{
		*(info + i) = *param;
		(info + i)->pos = i + 1;
		if (i > 0)
			(info + i)->lfork = fork + i - 1;
		else
			(info + i)->lfork = fork + param->number - 1;
		(info + i)->rfork = fork + i;
		pthread_mutex_init(fork + i, NULL);
	}
}

static void	threadinator(pthread_t *philo, t_param *info, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < info->number)
	{
		pthread_create(philo + i, NULL, &philo_routine, info + i);
	}
	i = -1;
	while (++i < info->number)
	{
		if (time_since((info + i)->lastmeal) > info->death)
		{
			pthread_mutex_lock(info->speachrod);
			info->flagdeath[0]++;
			printf("%d	%d died\n", time_since(info->start), i);
			pthread_mutex_unlock(info->speachrod);
			break ;
		}
		if (i == info->number - 1)
			i = -1;
	}
	i = -1;
	while (++i < info->number)
		pthread_join(*(philo + i), NULL);
	i = -1;
	while (++i < info->number)
		pthread_mutex_destroy(fork + i);
}

static int	philo_alloc(pthread_mutex_t **fork, pthread_t **philo,
	t_param **info, t_param *param)
{
	*fork = malloc(sizeof(pthread_mutex_t) * param->number);
	if (fork == NULL)
		return (-1);
	*philo = malloc(sizeof(pthread_t) * param->number);
	if (philo == NULL)
	{
		free (fork);
		return (-1);
	}
	*info = malloc(sizeof(t_param) * param->number);
	if (info == NULL)
	{
		free (fork);
		free (philo);
		return (-1);
	}
	param->speachrod = malloc(sizeof(pthread_mutex_t));
	if (param->speachrod == NULL)
	{
		free (fork);
		free (philo);
		free (info);
		return (-1);
	}
	return (0);
}

int	create_thread(t_param *param)
{
	pthread_mutex_t	*fork;
	pthread_t		*philo;
	t_param			*info;

	if (philo_alloc(&fork, &philo, &info, param) == -1)
		return (-1);
	pthread_mutex_init(param->speachrod, NULL);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	init_philo(param, info, fork);
	threadinator(philo, info, fork);
	free (param->speachrod);
	free (fork);
	free (philo);
	free (info);
	return (0);
}
