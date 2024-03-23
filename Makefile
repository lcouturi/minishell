NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra

LDFLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib -Llibs/Libft -lft
CPPFLAGS = -I${HOME}/.brew/opt/readline/include -I/opt/homebrew/opt/readline/include

INCLUDE_DIR = ./include

MAIN = main signal strarrutils
CMD = cd cd_pwd echo env exec exec_error exec_proc exit export pwd unset
PARSER =  escape_split expand_envvar expand_wildcard get_arg_num get_file_list get_length is load_lst parser rm_quotes
REDIR = cmd_redir exec_redir utils_redir utils_redir2 utils_redir3
PIPE = utils_pipe utils_pipe2 utils_pipe3 utils_pipe4
GET_NEXT_LINE = get_next_line_bonus get_next_line_utils_bonus

SRCS =	$(addsuffix .c, $(MAIN)) \
		$(addsuffix .c, $(addprefix cmd/, $(CMD))) \
		$(addsuffix .c, $(addprefix parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix redirection/, $(REDIR))) \
		$(addsuffix .c, $(addprefix pipe/, $(PIPE))) \
		$(addsuffix .c, $(addprefix libs/get_next_line/, $(GET_NEXT_LINE)))

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRCS)
	@if [ ! -d /Users/$(USER)/.brew ]; then \
		echo "\033[1;32mInstalling brew:\033[0m"; \
		curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
		echo "\033[1;32mBrew installed\033[0m"; \
	fi
	@if [ ! -d /Users/$(USER)/.brew/opt/readline ]; then \
		echo "\033[1;32mInstalling readline:\033[0m"; \
		source ~/.zshrc \
		brew install readline; \
		brew link --force readline; \
		echo "\033[1;32mReadline installed\033[0m"; \
	fi
	@make bonus -s -C libs/Libft
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRCS) -o $(NAME)

bonus : $(OBJS)
	@make bonus -s -C libs/Libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)_bonus

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
	@make clean -s -C libs/Libft
	@rm -rf $(OBJS) "|" "<" ">" ">>" .temp asd grep lol minishell.dSYM minishell_test.log o out1 tmp_*

debug : fclean
	@make debug -s -C libs/Libft
	$(CC) $(CFLAGS) $(CPPFLAGS) -g -fsanitize=undefined $(LDFLAGS) $(SRCS) -o $(NAME)


fclean : clean
	@make fclean -s -C libs/Libft
	@rm -rf $(NAME) $(NAME)_bonus

re : fclean all

.PHONY : all, bonus, clean, debug, fclean, re, $(NAME),
