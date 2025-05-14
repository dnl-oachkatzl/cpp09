# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 19:08:54 by daspring          #+#    #+#              #
#    Updated: 2025/05/04 18:49:13 by daspring         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= c++
CXXFLAGS	= -g -Wall -Wextra -Werror -Wshadow -std=c++17
SRC			= 	main.cpp \
				PmergeMe.cpp
OBJ			= $(SRC:.cpp=.o)
TARGET		= PmergeMe

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
