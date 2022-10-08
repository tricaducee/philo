ECHO = @echo
PRINT = @printf
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
INVERT = \033[7m
RESETTXT = \033[0m
BOLD = \033[1m

RM = rm -rf

SRC =	$(wildcard *.c)

OBJ = $(SRC:.c=.o)

NAME = philosophers

CC = gcc

CFLAGS = -Wall -Werror -Wextra

ifeq ($(DEBUG), debug)
	CFLAGS += -fsanitize=address -g3
endif

$(NAME) : $(OBJ)
	$(ECHO) "$(YELLOW)Compilation de $(NAME)...$(RESETTXT)"
	@$(CC) $(CFLAGS) -o $@ $^
	$(ECHO) "$(GREEN)$(BOLD)Compilation Terminée !!!$(RESETTXT)"

%.o : %.c
	$(PRINT) "$(YELLOW)Generation des objets...$(RESETTXT)\r"
	@$(CC) $(CFLAGS) -o $@ -c $<

#bonus :
#	@make -C Checker

all : $(NAME)# bonus

clean :
	$(ECHO) "$(RED)Suppression des objets...$(RESETTXT)"
	@$(RM) $(OBJ)
	$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

#b_clean :
#	@make clean -C Checker

#all_clean : clean b_clean

fclean : clean
	$(ECHO) "$(RED)Suppression de $(NAME)...$(RESETTXT)"
	@$(RM) $(NAME)
	$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

#b_fclean :
#	@make fclean -C Checker

#all_fclean : fclean b_fclean

re : fclean $(NAME)

#b_re :
#	@make re -C Checker

#all_re : re b_re

.PHONY: all re clean fclean #bonus