# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swautele <swautele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 14:48:19 by swautele          #+#    #+#              #
#    Updated: 2022/03/29 17:36:58 by swautele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
FILES = src/philosophers.c \
	src/param.c \
	src/thread.c \
	src/ft_atoi.c \
	src/routine.c
CC = gcc
CFLAGS = -Wextra -Werror -Wall 
OBJECT = $(FILES:.c=.o)

all : $(NAME)

clean :
	rm $(OBJECT)

fclean : clean
	rm $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

.o : .c
	$(CC) $(CFLAGS) $? -o $@

test : $(NAME)
	./$(NAME) 3 1000 100 100

save :
	git commit -am autosave
	git push https://github.com/swautelet/philosophers.git

.phony : save test fclean clean