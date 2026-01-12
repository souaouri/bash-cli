# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 12:34:57 by souaouri          #+#    #+#              #
#    Updated: 2024/08/04 09:08:19 by souaouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
CC				+=	-Wall -Wextra -Werror 
# CC				+= -fsanitize=address -g
NAME 			=	minishell
HEADER 			=	minishell.h

LIBS = -L $(shell brew --prefix readline)/lib -lreadline
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

SRC = 	main.c parsing/lexer_list.c parsing/utils_string.c parsing/ft_split.c \
		parsing/tokenizer.c parsing/utils_free.c parsing/quotes_spaces.c parsing/utils_quotes_spaces.c \
		parsing/syntax_error.c parsing/utils_split.c parsing/expanding/quotes_expanding.c \
		parsing/libft_func.c parsing/expanding/expanding.c parsing/expanding/utils.c \
		parsing/utils.c parsing/remove_quotes.c parsing/parser/parser.c parsing/parser/utils_parser.c \
		parsing/parser/parser_files.c parsing/parser/cmds_op.c addresses_collector.c\
		parsing/parser/expand_heredoc.c \
		execution/src/exec.c execution/src/function_devision.c execution/src/print_errors.c execution/src/utile.c \
		execution/src/run_builtins.c execution/src/run_builtins_mul_cmd.c execution/builtins/cd.c execution/builtins/echo.c execution/builtins/pwd.c \
		execution/builtins_utils/export_utile_1.c execution/builtins_utils/export_utile_2.c execution/builtins_utils/export_utile_3.c \
		execution/builtins_utils/export_utile_4.c execution/builtins/env.c execution/builtins_utils/env_utile.c execution/builtins/exit.c \
		execution/builtins/export.c execution/builtins/unset.c execution/utils/utils_1.c execution/builtins_utils/cd_utile.c execution/builtins_utils/exit_utile.c \
		execution/utils/utils_2.c execution/utils/utils_3.c execution/utils/utils_4.c \
		execution/utils/utils_5.c execution/utils/utils_6.c signals.c \
		execution/utils/utils_7.c execution/utils/utils_8.c parsing/my_split.c \
		parsing/parser/herdoc.c parsing/expanding/expanding_utils.c parsing/expanding/expand_utils.c

OBJ = $(SRC:.c=.o)

TARGET = minishell

all : $(TARGET)

$(TARGET) : $(OBJ) minishell.h
	@$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBS)
	@echo "$(GREEN)[ + ] Compilation complete: $(TARGET) created successfully!$(RESET)"

%.o : %.c minishell.h
	@$(CC) $(FLAGS) -c -I $(LINKREADLINELIB1) $< -o $@

clean :
	@rm -rf $(OBJ)
	@echo "$(YELLOW)[ + ] Object files removed successfully!$(RESET)"

fclean : clean
	@rm -rf $(TARGET)
	@echo "$(YELLOW)[ + ] Executable '$(TARGET)' removed successfully!$(RESET)"

re : fclean all

RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m

# export > solimi | cat | cat | cat > solimi
# message error in parc and exec stop cmd to run becose infile=-1;
# message error "cmd not found"
# 5

#  //printf ("\n\n---> : %s\n\n", new);
# cat < Makefile > sssss
# dakchi nadii
# cat < Makefile | exit
# 00
# echo LLL | cat
# error !!: Invalid argument
# singl cmd builtins
#ls | ls | ls | cat < Makefile
#cat | cat | cat | ls -l
# get_content_from_eq_to_fin

# Tasks for soulaiman
# # 1- malloc
# 2- normitte
# # Tasks
#cd -

# tasks for me
# addspaces
# signals cat minishell : minishell : 
# getenv
# minishell : << "a" cat
# ls > 1 >> 2 >> 3 > 4 >> 5 >> 6 > 7


