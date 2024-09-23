#Target Binary Program
NAME = ping

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags
FLAGS = -Wall -Werror -Wextra -I includes -g

#Directory locations
MAIN_DIR = main/
UTILS_DIR = utils/
ERRORS_DIR = errors/
OBJS_DIR = obj/

#Sources by folder
_MAIN := main.c dns.c ping_loop.c ping.c
_UTILS := base_printing_utils.c
_ERRORS := error_return.c fatal_error.c

ALL_SRCS := $(addprefix $(MAIN_DIR), $(_MAIN)), \
			$(addprefix $(UTILS_DIR), $(_UTILS)), \
			$(addprefix $(UTILS_DIR), $(_UTILS))

SRCS = $(_MAIN) $(_UTILS) $(_ERRORS)

OBJ_FILES = $(SRCS:.c=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))
INCLUDES = includes/defines.h includes/ping.h includes/structs.h

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(INCLUDES)
	@cc $(FLAGS) $(OBJS) -o $@
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(COLOUR_BLUE)object directory created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(MAIN_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(UTILS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(ERRORS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

clean:
	@rm -f $(OBJS)
	@echo "$(COLOUR_BLUE)object directory cleaned$(COLOUR_END)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: fclean all
