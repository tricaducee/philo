# COLORS
BLUE	= \033[1;36m
RED 	= \033[1;31m
ORANGE	= \033[1;33m
RESET	= \033[0m

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g3

RM		=	rm -rf

FILES	=	$(wildcard *.c)

INCLUDE	=	philosophers.h

INCLUDE	=	-lpthread

NAME	=	philosophers

SRC 	=	$(FILES)
OBJ 	=	$(SRC:.c=.o)

all: $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "[$(BLUE) CREATED$(RESET) ] : *.o & executable : philosophers"

clean:
	@$(RM) $(OBJ)
	@echo "[$(RED) DELETED$(RESET) ] : all *.o files"

fclean: clean
	@$(RM) $(NAME)
	@echo "[$(RED) DELETED $(RESET)] : executable : $(NAME)"

re: fclean all

.PHONY: all clean fclean re%