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
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
