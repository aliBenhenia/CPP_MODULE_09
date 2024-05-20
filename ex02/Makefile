NAME = PmergeMe
CC = c++
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC =  main.cpp  PmergeMe.cpp
OBJ = $(SRC:%.cpp=%.o)
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME) 
%.o : %.cpp PmergeMe.hpp
	$(CC) $(CFLAGS)  -c $< -o $@
clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all
 