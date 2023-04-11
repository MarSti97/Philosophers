SRCS= philo.c tools.c list_funcs.c
FLAGS= -Wall -Werror -Wextra -pthread -g
NAME= philo
RM= rm -f

#Colors
GREEN=\033[0;32m
RED=\033[0;31m
END=\033[0m

all : $(NAME)

$(NAME) : $(SRCS)
	@cc $(FLAGS) $(SRCS) -o $(NAME)
	@echo "$(GREEN)<<<< Compiled >>>>$(END)"

clean :
	@$(RM) $(NAME)
	@echo "$(RED)<<<< Cleaned >>>>$(END)"

fclean : clean 
	@$(RM) $(BONUS_NAME)
	@echo "$(RED)<<<< All >>>>$(END)"

re : fclean all

.PHONY : all fclean clean re