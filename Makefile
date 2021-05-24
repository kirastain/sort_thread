NAME = sort
FLAGS = -std=c++14 -D_NDEBUG -O3 -lpthread
SRCS = ./Sort.cpp 
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(FLAGS)
	@echo "done"

%.o:%.cpp
	@g++ -o $@ -c $< $(FLAGS)

clean:
	@rm $(OBJS)
	@rm "output"
	@echo ".o files removed"

fclean: clean
	@rm $(NAME)
	@echo "Files removed"

inputclean:
	@rm input

cleantemps:
	@rm temp*

generate:
	@g++ -o generate $(FLAGS) Generate.cpp
	@./generate

test_sort:
	@g++ -o generate_test $(FLAGS) GenerateTest.cpp
	@./generate_test

re: fclean all

.PHONY: all clean fclean re test generate inputclean cleantemps