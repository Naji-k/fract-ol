# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nakanoun <nakanoun@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/13 23:10:52 by nakanoun      #+#    #+#                  #
#    Updated: 2023/02/13 23:10:52 by nakanoun      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol
CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code -Ofast -fsanitize=address

#Lib
LIBMLX	:= ./lib/MLX42
LIB_PRINTF	:= ./lib/ft_printf/libftprintf.a
LIB_LIBMLX	:= $(LIBMLX)/build/libmlx42.a

#Directories
PRINTF_DIR = ./lib/ft_printf
LIBFT_DIR = ./lib/ft_printf/libft
OBJ_DIR = obj

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(PRINTF_DIR)/include -I $(LIBFT_DIR)
LIBS	:= $(LIBMLX)/build/libmlx42.a -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
SRCS	:= $(shell find ./src -iname "*.c")
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all:  $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(HEADERS) $(ASAN_FLAGS) -o $@ -c $<  && printf "Compiling: $(notdir $<)"

$(NAME):	$(LIB_LIBMLX) $(LIB_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBS) $(LIB_PRINTF)  -o $(NAME)

$(LIB_PRINTF):
	@make -C $(PRINTF_DIR)

$(LIB_LIBMLX):
	@cmake $(LIBMLX) -DDEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

clean:
	rm -rf $(OBJ_DIR);
	@rm -r $(LIBMLX)/build
	@make clean -C $(PRINTF_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(PRINTF_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libmlx