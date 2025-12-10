CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJS = main.o Seeds.o Voronoi.o
TARGET = voronoi

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Seeds.hpp Voronoi.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Seeds.o: Seeds.cpp Seeds.hpp
	$(CXX) $(CXXFLAGS) -c Seeds.cpp

Voronoi.o: Voronoi.cpp Voronoi.hpp Seeds.hpp
	$(CXX) $(CXXFLAGS) -c Voronoi.cpp

clean:
	rm -f $(OBJS) $(TARGET) *.gcno *.gcda *.gcov callgrind.out.*

.PHONY: all clean

profile: $(TARGET)
	valgrind --tool=callgrind ./$(TARGET)

coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage -g -O0
coverage: clean $(TARGET)
	./$(TARGET)
	gcov -b -c main.cpp
	gcov -b -c Voronoi.cpp
	gcov -b -c Seeds.cpp

memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)