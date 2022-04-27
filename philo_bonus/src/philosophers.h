/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:12:43 by swautele          #+#    #+#             */
/*   Updated: 2022/04/27 14:27:49 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# define D printf("< %d:%s %s() [%d] >\n", __LINE__, __FILE__, __FUNCTION__, data->meal);

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_param{
	int				number;
	int				death;
	int				eat;
	int				sleep;
	int				meal;
	int				pos;
	sem_t			*forks;
	struct timeval	start;
	struct timeval	lastmeal;
	char			*flagdeath;
	sem_t			*speachrod;
}	t_param;

int		ft_atoi(const char *str, char *flagerr);
int		create_process(t_param *param);
t_param	*init_param(int argc, char **argv);
void	*philo_routine(void *info);
int		time_since(struct timeval last);
int		my_sleep(int time, t_param *data);
int		philo_die(t_param *data);

#endif
