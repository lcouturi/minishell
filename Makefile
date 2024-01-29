NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 

LDFLAGS = -lreadline -L/opt/homebrew/opt/readline/lib -L${HOME}/.brew/opt/readline/lib -Llibs/Libft -lft
CPPFLAGS = -I${HOME}/.brew/opt/readline/include -I/opt/homebrew/opt/readline/include

INCLUDE_DIR = ./include

MAIN = main signal
CMD = cd echo env exec exit export pwd unset
PARSER =  arg_splitter expand_envvar expand_wildcard get_file_list parser rm_quotes
REDIR = cmd_redir exec_redir utils_redir
PIPE = utils_pipe utils

SRCS =	$(addsuffix .c, $(MAIN)) \
		$(addsuffix .c, $(addprefix cmd/, $(CMD))) \
		$(addsuffix .c, $(addprefix parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix redirection/, $(REDIR))) \
		$(addsuffix .c, $(addprefix pipe/, $(PIPE))) 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make bonus -s -C libs/Libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
	@make clean -s -C libs/Libft
	@rm -rf $(OBJS)

debug : fclean $(OBJS)
	@make debug -s -C libs/Libft
	$(CC) $(CFLAGS) -g -fsanitize=thread $(LDFLAGS) $(OBJS) -o $(NAME)


fclean : clean
	@make fclean -s -C libs/Libft
	@rm -rf $(NAME)

re : fclean all

.PHONY : all, clean, debug, fclean, re, $(NAME),
