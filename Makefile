.PHONY: all compile run valgrind clean doc
.DEFAULT_GOAL = all

CXX = g++
CXXFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++17
CXXFLAGSANITIZE = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++17 -fsanitize=address
EXEC = janeclu4
SOURCE := $(wildcard src/*.cpp)

all: compile doc

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp > $*.d


compile: $(SOURCE:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(SOURCE:.cpp=.o) -o $(EXEC)

comp_sanitizer: $(SOURCE:.cpp=.o)
	$(CXX) $(CXXFLAGSANITIZE) $(SOURCE:.cpp=.o) -o $(EXEC)

sanitizer : comp_sanitizer
	./$(EXEC)

run : compile
	./$(EXEC)

valgrind: compile
	valgrind ./$(EXEC)

clean:
	rm -f src/*.o src/*.d $(EXEC)
	rm -r doc
doc:
	doxygen Doxyfile

-include $(SOURCE:.cpp=.d)
