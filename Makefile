CXX = g++

flags = -Wall -std=c++17 
ldflags = -lSDL2

target = game

#add any of new sources here
srcs = main.cpp

objs = $(srcs:.cpp=.o)

all: $(target)

$(target): $(objs)
	$(CXX) $(flags) -o $(target) $(objs) $(ldflags)

%.o: %.cpp
	$(CXX) $(flags) -c $< -o $@

run: $(target)
	./$(target)
	
clean:
	rm -f $(target) $(objs)




