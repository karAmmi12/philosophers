# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kammi <kammi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 17:13:23 by kammi             #+#    #+#              #
#    Updated: 2024/06/12 16:22:55 by kammi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#########################################################
## ARGUMENTS

NAME = philo
HEADER = includes/philo.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g -pthread
MAKE_LIB = ar -rcs

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m


##########################################################
## SOURCES

SRCS = srcs/main.c\
		srcs/parser.c\
		srcs/actions.c\
		srcs/libft.c\
		srcs/utils.c\
		srcs/init.c\
		srcs/death.c\

OBJS = $(SRCS:.c=.o)



##########################################################
## RULES

all : $(NAME)


$(NAME) : $(OBJS)
	@echo "$(GREEN)Linking libraries and building $@...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Success \n$(RESET)"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
 :

clean :
	@echo "$(RED)Cleaning object files...🧹$(RESET)"
	@$(RM) $(OBJS) $(ARCHIVE)


fclean : clean
	@echo "$(RED)Cleaning all files...🧹$(RESET)"
	@$(RM) $(NAME)


re : fclean all

.PHONY : all clean fclean re
