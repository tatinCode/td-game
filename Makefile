CXX = g++

flags = -Wall -g

target = game

#add any of new sources here
srcs = main.cpp

objs = $(srcs:.cpp=.o)

all: $(target)

$(target): $(objs)
	$(CXX) $(flags) -o $(target) $(objs)

%.o: %.cpp
	$(CXX) $(flags) -c $< -o $@

run: $(target)
	./$(target)
	
clean:
	rm -f $(target) $(objs)




