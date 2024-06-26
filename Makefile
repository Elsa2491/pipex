NAME = pipex
BONUS_NAME = pipex_bonus
PRINTF = ./printf/libftprintf.a
CFLAGS = -Wall -Wextra -Werror -g
SRCS_PATH = srcs/
OBJS_PATH = objs/
BONUS_SRCS_PATH = bonus/srcs/
BONUS_OBJS_PATH = bonus/objs/
GREEN 	:= \e[32m
RESET 	:= \e[0m
MAKEFLAGS    +=    --no-print-directory

SRCS = main.c split.c size_functions.c get_path.c handle_errors.c \
	print_errors.c handle_path.c handle_access.c handle_spaces_and_slashes.c \
	handle_processes.c string_functions.c \

BONUS_SRCS = main_bonus.c split_bonus.c size_functions_bonus.c get_path_bonus.c handle_errors_bonus.c \
	print_errors_bonus.c handle_path_bonus.c handle_access_bonus.c \
	handle_spaces_and_slashes_bonus.c handle_processes_bonus.c string_functions_bonus.c \
	here_doc_bonus.c get_next_line.c get_next_line_utils.c wait_and_close_bonus.c \

OBJ = $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
BONUS_OBJ = $(addprefix $(BONUS_OBJS_PATH), $(BONUS_SRCS:.c=.o))

all: $(NAME)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(BONUS_OBJS_PATH):
	@mkdir -p $(BONUS_OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	cc $(CFLAGS) -c $< -o $@

$(BONUS_OBJS_PATH)%.o: $(BONUS_SRCS_PATH)%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH) $(OBJ)
	@echo "\nCompilation mandatory part: $(GREEN)success$(RESET)\n"
	make --no-print-directory -C "./printf"
	cc $(CFLAGS) $(OBJ) -Inc $(PRINTF) -o $(NAME)
	@echo "\nCompilation $(GREEN)finished$(RESET)!\n"

$(BONUS_NAME): $(BONUS_OBJS_PATH) $(BONUS_OBJ)
	@echo "\nCompilation bonus part: $(GREEN)success$(RESET)\n"
	make --no-print-directory -C "./printf"
	cc $(CFLAGS) $(BONUS_OBJ) -Inc $(PRINTF) -o $(BONUS_NAME)
	@echo "\nCompilation $(GREEN)finished$(RESET)!\n"

bonus:
	@make $(BONUS_NAME)

clean:
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJS_PATH)
	@echo "\nMandatory files objects and associated directories removed\n"
	/bin/rm -rf $(BONUS_OBJ)
	/bin/rm -rf $(BONUS_OBJS_PATH)
	@echo "\nBonus files objects and associated directories removed\n"

fclean: clean
	/bin/rm -rf $(NAME) $(BONUS_NAME) $(PRINTF)
	@echo "\npipex destroyed\n"
	make fclean -C printf

re: fclean all

.PHONY: all clean fclean re bonus
