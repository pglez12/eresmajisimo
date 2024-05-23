NAME    := minishell
CFLAGS  := -Wall -Wextra -Werror -g 
LDFLAGS := -L/home/linuxbrew/.linuxbrew/opt/readline/lib -lreadline

HEADERS := -I./includes -I/home/linuxbrew/.linuxbrew/opt/readline/include
LIBFT   := ./src/libft
LIBS    := $(LIBFT)/libft.a

EXE_DIR = src/executor_src
PAR_DIR = src/parser_src
UTILS_DIR = src/utils_src
BI_DIR = src/build_ins_src


SRCS    :=	src/main.c\
			$(PAR_DIR)/fill_lst.c \
			$(EXE_DIR)/execute.c $(EXE_DIR)/cmd_exec.c \
			$(EXE_DIR)/cmd_path.c $(EXE_DIR)/cmd_redir_exec.c \
			$(BI_DIR)/built_ins.c $(EXE_DIR)/envp_lst.c \
			$(EXE_DIR)/checks_cmds.c $(EXE_DIR)/cmd_redir_utils.c \
			$(UTILS_DIR)/clear.c $(BI_DIR)/ft_cd.c $(BI_DIR)/ft_exit.c \
			$(BI_DIR)/ft_unset.c $(BI_DIR)/ft_export.c $(BI_DIR)/ft_export_utils.c \
			$(UTILS_DIR)/ft_strutils.c $(UTILS_DIR)/signals.c $(UTILS_DIR)/clear2.c\
			$(EXE_DIR)/heredoc.c $(UTILS_DIR)/automata.c $(UTILS_DIR)/fill_cmd_lst.c\
			$(UTILS_DIR)/fill_files_lst.c $(UTILS_DIR)/fill_token.c $(PAR_DIR)/get_token.c\
			$(UTILS_DIR)/ft_strdouble_utils.c $(PAR_DIR)/dep_var.c $(UTILS_DIR)/ft_split_moded.c\
			$(PAR_DIR)/t_fill_utils.c $(PAR_DIR)/quotes.c $(PAR_DIR)/fill_utils.c\
			$(PAR_DIR)/dep_var_utils.c $(PAR_DIR)/get_token_utils.c\
			$(PAR_DIR)/quotes_files.c $(PAR_DIR)/dep_var_files.c

OBJS    := ${SRCS:.c=.o}

all: lib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

lib:
	@make -C $(LIBFT) all

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJSLIB)
	@rm -f $(LIBS)
	@make clean -C ./src/libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./src/libft

re: clean all

.PHONY: all, clean, fclean, re
