CC= cc -Werror -Wextra -Wall -Ilibft/headers -I.

SRC= main.c \
	src/child_processes.c \
	src/destroy.c \
	src/parsing.c

O_DIR= obj/
OBJ= $(SRC:%.c=$(O_DIR)%.o)

NAME= pipex

LIBFT= libft/libft.a
LIBPATH= libft/

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo -n "\033[32m\nSuccessfully Generated \033[0m$(NAME) \n\n"

$(O_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@echo "\033[95mCompiling\033[0m $(notdir $<)"
	@sleep 0.0001
	@$(CC) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBPATH)

clean:
	@echo "\033[95mCleansing $(NAME) Objects"
	@sleep 0.7
	@echo -n "."
	@sleep 0.2
	@echo -n "."
	@sleep 0.2
	@echo ".\033[0m"
	@sleep 0.2
	@make --no-print-directory -C $(LIBPATH) clean
	@rm -rf $(O_DIR)

fclean:
	@make --no-print-directory -C $(LIBPATH) fclean
	@echo "\033[95mCleansing $(NAME)"
	@sleep 0.7
	@echo -n "."
	@sleep 0.2
	@echo -n "."
	@sleep 0.2
	@echo ".\033[0m"
	@sleep 0.2
	@rm -rf $(O_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: $(LIBFT) re fclean clean