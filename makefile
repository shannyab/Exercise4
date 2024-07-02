CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -I.
TARGET = tree
TEST= test

MAIN = main.cpp complex.cpp
TESTS= test.cpp complex.cpp
OBJS = $(MAIN:.cpp=.o)
TEST_OBJS = $(TESTS:.cpp=.o)

all: $(TARGET) $(TEST)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system

$(TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(TEST_OBJS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
