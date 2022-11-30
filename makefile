#------------------------------------------------------------------------------#
#								   GENERAL									   #
#------------------------------------------------------------------------------#
NAME = minishell
#NAME_BONUS = minishell_bonus

CC = gcc
# CFLAGS = -g -Wall -Werror -Wextra
CFLAGS = -g -Wall -Werror -Wextra -fsanitize=address
RM = rm -rf

#------------------------------------------------------------------------------#
#								   LIBRARIES								   #
#------------------------------------------------------------------------------#
D_LIBFT = libft/
LIBFT = libft/libft.a
D_LIBFTHEAD = libft/includes/libft.h

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
		src/struct_define.c \
		src/built_in.c \
		src/built_in2.c \
		src/explore_readline.c \
		src/quote_management.c \
		src/meta_analyzis.c

#HEADER_BONUS = includes/minishell_bonus.h
#D_SRC_BONUS = src_bonus/
#D_OBJ_BONUS = obj_bonus/
#OBJS_BONUS = $(patsubst $(D_SRC_BONUS)%.c,$(D_OBJ_BONUS)%.o,$(SRCS_BONUS))

#------------------------------------------------------------------------------#
#									 RULES									   #
#------------------------------------------------------------------------------#

all:	deadpool $(NAME)

#-lcurses pour les signaux
$(NAME):	$(LIBFT) $(LIBRL) $(OBJS)
	@$(call creating, $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBRL) -lreadline -lcurses -o $@)
	@echo "$(LGREEN)Software Compilation completed ...!$(NC)"
#automatic launch
	@sleep 2
	@clear
#	@$(call intro_minishell)
#	@./minishell
# À changer au moment du rendu

deadpool:
	@$(call intro_mandatory)

$(LIBFT): $(D_OBJ) $(D_LIBFTHEAD)
	@$(MAKE) -C $(D_LIBFT)

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

clean:
	@$(call cleaning, $(RM) $(D_OBJ))
#	@$(RM) $(D_OBJ_BONUS)

fclean:	clean
	@$(call fcleaning, $(RM) $(NAME))
#	@$(RM) $(NAME_BONUS)

lclean: fclean
	@$(call lcleaning)
	@$(MAKE) -s --no-print-directory -C $(D_LIBFT) fclean
	@$(MAKE) -s --no-print-directory -C $(D_LIBRL) distclean

re:	fclean all

.PHONY: all clean fclean lclean re

#------------------------------------------------------------------------------#
#									IF BONUS								   #
#------------------------------------------------------------------------------#

#SRCS_BONUS = src_bonus/...

#deadpool_bonus:
#	@$(call intro_bonus)

#$(NAME_BONUS): deadpool_bonus $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) $(D_LIBFT)$(LIBFT) $(D_LIBRL)$(LIBRL)
#	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(NC)\r"
#	@echo "$(LGREEN)Software Compilation completed !$(NC)"

#$(OBJS_BONUS): $(D_OBJ_BONUS)%.o : $(D_SRC_BONUS)%.c $(HEADER_BONUS)
#		@mkdir -p $(D_OBJ_BONUS)
#		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

#bonus: deadpool_bonus do_libft $(NAME_BONUS)

#------------------------------------------------------------------------------#
#								  MAKEUP RULES								   #
#------------------------------------------------------------------------------#

#----------------------------------- SOURCE -----------------------------------#
D_INTRO = pretty/

#----------------------------------- INTROS -----------------------------------#
define intro_mandatory
@bash $(D_INTRO)intro_daftpunk.sh
endef

define intro_bonus
@bash $(D_INTRO)intro_bonus.sh
endef

define intro_minishell
@bash $(D_INTRO)intro_minishell.sh
endef
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