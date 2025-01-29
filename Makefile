# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 14:15:54 by icunha-t          #+#    #+#              #
#    Updated: 2025/01/29 18:25:44 by icunha-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = server
NAME_BONUS = server_bonus
CLIENT_NAME = client
CLIENT_NAME_BONUS = client_bonus
SRCS_PATH = ./srcs/
SRCS_SERVER = $(addprefix $(SRCS_PATH), server.c)
SRCS_CLIENT = $(addprefix $(SRCS_PATH), client.c)
SRCS_SERVER_BONUS = $(addprefix $(SRCS_PATH), server_bonus.c)
SRCS_CLIENT_BONUS = $(addprefix $(SRCS_PATH), client_bonus.c)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

LIBFT_DIR = ./libft/
LIBFT = ./libft/libft.a

#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc

FLAGS = -Wall -Werror -Wextra
FLAGS += -g

RM = rm -f

AR = ar rcs

MAKE = make
#==============================================================================#
#                                  COLORS                                      #
#==============================================================================#
RED		= "\033[0;31m"
GREEN		= "\033[0;32m"  
YELLOW		= "\033[0;33m" 
RESET		= "\033[0m"
#==============================================================================#
#                               RULES & DEPS                                   #
#==============================================================================#
all: $(LIBFT) $(NAME) $(CLIENT_NAME)

bonus: $(LIBFT) all $(NAME_BONUS) $(CLIENT_NAME_BONUS)

%.o: %.c 
	@$(C_COMP) $(FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo $(GREEN) "$(NAME) was created successfully!" $(RESET)

$(CLIENT_NAME): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(CLIENT_NAME)
	@echo $(GREEN) "$(CLIENT_NAME) was created successfully!" $(RESET)
	
$(NAME_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS_SERVER_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME_BONUS)
	@echo $(GREEN) "$(NAME_BONUS) was created successfully!" $(RESET)

$(CLIENT_NAME_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS_CLIENT_BONUS) -L$(LIBFT_DIR) -lft -o $(CLIENT_NAME_BONUS)
	@echo $(GREEN) "$(CLIENT_NAME_BONUS) was created successfully!" $(RESET)
#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
clean:
	@$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)
	@echo $(RED) "All .o files were deleted in minitalk!" $(RESET)

clean_bonus:
	@$(RM) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	@echo $(RED) "All .o bonus files were deleted in minitalk!" $(RESET)

cleanall: clean clean_bonus
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME) $(CLIENT_NAME)
	@echo $(RED) "$(NAME) and $(CLIENT_NAME) were deleted!" $(RESET)

fclean_bonus: clean_bonus
	@$(RM) $(NAME_BONUS) $(CLIENT_NAME_BONUS)
	@echo $(RED) "$(NAME) and $(CLIENT_NAME_BONUS) were deleted!" $(RESET)

fcleanall: fclean fclean_bonus
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean fclean_bonus all

.PHONY: all bonus clean clean_bonus fclean fclean_bonus re cleanall fcleanall