/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/23 13:26:29 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	init_philo(t_param *param, t_param *info, pthread_mutex_t *fork)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < param->number)
// 	{
// 		*(info + i) = *param;
// 		(info + i)->pos = i + 1;
// 		if (i > 0)
// 			(info + i)->lfork = fork + i - 1;
// 		else
// 			(info + i)->lfork = fork + param->number - 1;
// 		(info + i)->rfork = fork + i;
// 		pthread_mutex_init(fork + i, NULL);
// 	}
// }
static void	kill_child(int id[200], t_param *data)
{
	(void)id;
	int	ret;
	int	i;
	int	j;

	ret = 0;
	i = 200;
	while (i >= 0)
	{
		i = waitpid(0, &ret, 0);
		// j = WEXITSTATUS(ret);
		// printf("i = %d		ret = %d\n", i, WEXITSTATUS(ret));
		if (WEXITSTATUS(ret) == 1)
		{
			// printf("data->number = %d\n", data->number);
			j = -1;
			// usleep(1000);
			while (++j < data->number)
			{
				// printf("kill id %d\n", id[j]);
				kill(id[j], SIGINT);
			}
			sem_post(data->speachrod);
		}
	}
	// printf("test\n");
}

static void	processinator(t_param *data)
{
	int	i;
	int	id[200];

	memset(id, 0, sizeof(int) * 200);
	i = 0;
	while (++i <= data->number)
	{
		id[i - 1] = fork();
		if (id[i - 1] == 0)
		{
			data->pos = i;
			philo_routine(data);
			exit (0);
		}
	}
	kill_child(id, data);
	sem_close(data->forks);
	sem_close(data->speachrod);
}

int	create_process(t_param *param)
{
	sem_unlink("/forks");
	sem_unlink("/speach");
	param->speachrod = sem_open("/speach", O_CREAT, S_IRUSR | S_IWUSR, 1);
	param->forks = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR,
			param->number);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	processinator(param);
	return (0);
}
