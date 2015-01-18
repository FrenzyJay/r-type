# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: garm <garm@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/08/26 23:49:31 by garm              #+#    #+#              #
##   Updated: 2015/01/17 09:15:52 by garm             ###   ########.fr       ##
#                                                                              #
# **************************************************************************** #

CC = g++

NAME = ft_gkrellm

SOURCES_DIR = .
INCLUDES_DIR = .

ifeq ($(DEBUG), 1)
	FLAGS = -g -Wall -Wextra
	CC = g++
else
	FLAGS = -Wall -Werror -Wextra
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CFLAGS += $(FLAGS) -I $(INCLUDES_DIR)

DEPENDENCIES = \

SOURCES = \
		  $(SOURCES_DIR)/main.cpp \
		  $(SOURCES_DIR)/collision.cpp \

OBJS = $(SOURCES:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(DEPENDENCIES)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	@echo Creating $(NAME)...
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

clean:
	@rm -f $(OBJS)
	@echo Deleting $(NAME) OBJECTS files...

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM
	@echo Deleting $(NAME)...

re: fclean all

.PHONY: clean fclean re all

