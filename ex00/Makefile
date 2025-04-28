# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 19:08:54 by daspring          #+#    #+#              #
#    Updated: 2025/04/28 17:42:21 by daspring         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++17
SRC			= main.cpp \
			  BitcoinExchange.cpp
OBJ			= $(SRC:.cpp=.o)
TARGET		= btc

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(TARGET)

re : fclean all

.PHONY : all clean fclean re
