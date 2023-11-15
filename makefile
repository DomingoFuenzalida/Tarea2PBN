CXX = g++
CXXFLAGS = -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self

SRCS = main.cpp personaje.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
