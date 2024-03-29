#------------------------------------------------------------------------------#
#								   GENERAL									   #
#------------------------------------------------------------------------------#
NAME = minishell
#NAME_BONUS = minishell_bonus

CC = gcc
#CC = gcc-11
CFLAGS = -g -Wall -Werror -Wextra
#CFLAGS = -g -Wall -Wextra -Werror -fsanitize=leak
# CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf

#LSAN_OPTIONS=detect_leaks=1 ./minishell

#------------------------------------------------------------------------------#
#								   LIBRARIES								   #
#------------------------------------------------------------------------------#
D_LIBFT = libft/
LIBFT = libft/libft.a
D_LIBFTHEAD = libft/includes/libft.h

D_LIBART = libart/
LIBART = libart/libart.a
D_LIBARTHEAD = libart/includes/libart.h

# Pour faire fonctionner readline, modification du code dans keymap.h, readline.h et history.h
# Il faut enlever les conditions "if" autour de rlstdc.h (et les autres .h)
RLCONF = librl/config.log
D_LIBRL = librl/
LIBRL = librl/libhistory.a librl/libreadline.a

#------------------------------------------------------------------------------#
#									SOURCES									   #
#------------------------------------------------------------------------------#
HEADER = includes/minishell.h
D_SRC = src/
D_OBJ = obj/
OBJS = $(patsubst $(D_SRC)%.c,$(D_OBJ)%.o,$(SRCS))
SRCS =	src/minishell.c \
		src/personnal_fonction.c \
		src/built_in.c \
		src/built_in2.c \
		src/explore_readline.c \
		src/quote_management.c \
		src/quote_management_2.c \
		src/meta_analyzis.c \
		src/meta_analyzis2.c \
		src/parsing_utils.c \
		src/error_management.c\
		src/minishell_utils.c\
		src/minishell_utils2.c\
		src/built_in_utils.c\
		src/dollar_utils.c\
		src/redirection_management.c\
		src/redir_in_same_array.c\
		src/redir_in_same_array_2.c\
		src/redirection_utils.c\
		src/redirection_utils_2.c\
		src/redirection_utils_3.c\
		src/minus_utils.c\
		src/pipe_utils.c\
		src/heredoc.c\
		src/io_utils.c\
		src/prog_utils.c\
		src/explore_utils.c\
		src/detached_quote.c\
		src/detached_quote_utils.c\
		src/pipe_management.c\
		src/signal_management.c\
		src/dollar_parsing_utils.c\
		src/cleaning.c\
		src/init_data.c

#retire : 		src/redir_in_next_array.c

#HEADER_BONUS = includes/minishell_bonus.h
#D_SRC_BONUS = src_bonus/
#D_OBJ_BONUS = obj_bonus/
#OBJS_BONUS = $(patsubst $(D_SRC_BONUS)%.c,$(D_OBJ_BONUS)%.o,$(SRCS_BONUS))

#------------------------------------------------------------------------------#
#									 RULES									   #
#------------------------------------------------------------------------------#

all:	daftpunk $(NAME)

#-lcurses pour les signaux
$(NAME):	$(LIBFT) $(LIBART) $(LIBRL) $(OBJS)
	@$(call creating, $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBART) $(LIBRL) -lreadline -lcurses -o $@)
	@echo "$(LGREEN)Software Compilation completed ...!$(NC)"
	@sleep 2
	@clear

daftpunk:
	@$(MAKE) intro_daftpunk -C $(D_LIBART)

$(LIBFT): $(D_OBJ) $(D_LIBFTHEAD)
	@$(MAKE) -C $(D_LIBFT)

$(LIBART): $(D_OBJ) $(D_LIBARTHEAD)
	@$(MAKE) -C $(D_LIBART)

$(LIBRL):
	@echo "$(LGREEN)LIB READLINE Configuration started ...$(NC)"
	@cd librl && ./configure --silent
	@echo "$(LGREEN)LIB READLINE Configuration completed ...$(NC)"
	@echo "$(LGREEN)LIB READLINE Compilation started ...$(NC)"
	@$(MAKE) -s -C $(D_LIBRL)
	@echo "$(LGREEN)LIB READLINE Compilation completed ...$(NC)"

$(D_OBJ):
	@mkdir -p $(D_OBJ)

$(OBJS): $(D_OBJ)%.o : $(D_SRC)%.c $(HEADER)
		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)


#norm a checker
norm:
	@includes/ norminette

clean:
	@$(call cleaning, $(RM) $(D_OBJ))
#	@$(RM) $(D_OBJ_BONUS)

fclean:	clean
	@$(call fcleaning, $(RM) $(NAME))
#	@$(RM) $(NAME_BONUS)

lclean: fclean
	@$(call lcleaning)
	@$(MAKE) -s --no-print-directory -C $(D_LIBFT) fclean
	@$(MAKE) -s --no-print-directory -C $(D_LIBART) fclean
	@$(MAKE) -s --no-print-directory -C $(D_LIBRL) distclean

re:	fclean all

.PHONY: all clean fclean lclean re

#------------------------------------------------------------------------------#
#									IF BONUS								   #
#------------------------------------------------------------------------------#

#SRCS_BONUS = src_bonus/...

#daftpunk_bonus:
#	@$(call intro_bonus)

#$(NAME_BONUS): daftpunk_bonus $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) $(D_LIBFT)$(LIBFT) $(D_LIBRL)$(LIBRL)
#	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(NC)\r"
#	@echo "$(LGREEN)Software Compilation completed !$(NC)"

#$(OBJS_BONUS): $(D_OBJ_BONUS)%.o : $(D_SRC_BONUS)%.c $(HEADER_BONUS)
#		@mkdir -p $(D_OBJ_BONUS)
#		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

#bonus: daftpunk_bonus do_libft $(NAME_BONUS)

#------------------------------------------------------------------------------#
#								  MAKEUP RULES								   #
#------------------------------------------------------------------------------#

#----------------------------------- SOURCE -----------------------------------#
#D_PRETTY = pretty/

#----------------------------------- INTROS -----------------------------------#

#----------------------------------- COLORS -----------------------------------#
LRED = \033[91m
RED = \033[91m
LGREEN = \033[92m
LYELLOW = \033[93
LMAGENTA = \033[95m
LCYAN = \033[96m
NC = \033[0;39m

#----------------------------------- TEXTES -----------------------------------#
OK_STRING = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING = "[WARNING]"
COMP_STRING = "Generating"
CLEAN_STRING = "Cleaning"
CREAT_STRING = "Creating"

#----------------------------------- DEFINE -----------------------------------#
define run_and_test
printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(NC)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)" "💥$(NC)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)" "⚠️$(NC)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)" "✅$(NC)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define cleaning
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) OBJECT Files$(NC)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) OBJECT Files" "💥$(NC)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) OBJECT Files" "⚠️$(NC)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) OBJECT Files" "✅$(NC)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define fcleaning
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files$(NC)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files" "💥$(NC)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files" "⚠️$(NC)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files" "✅$(NC)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define lcleaning
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBRARY Files$(NC)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBRARIES Files" "💥$(NC)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBRARIES Files" "⚠️$(NC)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBRARIES Files" "✅$(NC)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define creating
printf "%b" "$(LCYAN)$(CREAT_STRING)$(LMAGENTA) $(@F)$(NC)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CREAT_STRING)$(LMAGENTA) $(@F)" "💥$(NC)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CREAT_STRING)$(LMAGENTA) $(@F)" "⚠️$(NC)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CREAT_STRING)$(LMAGENTA) $(@F)" "✅$(NC)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef