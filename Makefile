# Compilation
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g

# Names
NAME				=	pipex
NAME_BONUS			=	pipex_bonus

# Sources & Includes
SRCS				= 	srcs/main.c \
						srcs/utils.c
SRCS_BONUS			= 	srcs_bonus/main_bonus.c \
						srcs_bonus/utils_bonus.c \
						srcs_bonus/cmdhelper_bonus.c
OBJ_FOLDER			=	objs
LIB					=	libft/libft.a
INCLUDES			=	includes
INCLUDES_BONUS		=	includes_bonus

# Objects
OBJS				=	$(patsubst srcs/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))
OBJS_BONUS			=	$(patsubst srcs_bonus/%.c, $(OBJ_FOLDER)/%.o, $(SRCS_BONUS))

# Custom Makefile Flags
MAKEFLAGS			+=	--no-print-directory --silent

# Custom Colors
PURPLE				=	\033[1;35m
LIGHT_GREEN			=	\033[1;32m
RESET				=	\033[0m

# Custom messages
EXE_DONE			=	@echo "🎉$(PURPLE) $(NAME) compiled! 🎉$(RESET)\n"
BONUS_DONE			=	@echo "🎉$(PURPLE) $(NAME_BONUS) compiled! 🎉$(RESET)\n"
ALL_CLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all : check_relink

check_relink:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir $(OBJ_FOLDER); \
	fi
	@if [ -f $(NAME) ]; then \
		echo '✅$(LIGHT_GREEN) Nothing to be done for "all"! ✅$(RESET)\n'; \
	else \
		$(MAKE) $(NAME); \
	fi

bonus :
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir $(OBJ_FOLDER); \
	fi
	@if [ -f $(NAME_BONUS) ]; then \
		echo '✅$(LIGHT_GREEN) Nothing to be done for "all"! ✅$(RESET)\n'; \
	else \
		$(MAKE) $(NAME_BONUS); \
	fi

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) -I $(INCLUDES)
	$(EXE_DONE)

$(NAME_BONUS): libft $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIB) -o $(NAME_BONUS) -I $(INCLUDES_BONUS)
	$(BONUS_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER)/%.o: srcs_bonus/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

libft : 
	@if [ ! -f $(LIB) ]; then \
        $(MAKE) -C ./libft; \
	fi

clean :
	$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

re : fclean all

rebonus : fclean bonus

f : $(NAME)

fb : $(NAME_BONUS)

.PHONY: all clean fclean re libft f bonus fb rebonus
