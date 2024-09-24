CXX = g++

CXX_FLAGS = -I ./include/ -D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra  -Wunused -Wpedantic -Wshadow -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

#variables for arc-algorithm
SRCS = src/main.cpp
OBJ = $(patsubst %.cpp, build/%.o, $(subst src/, , $(SRCS))) 
EXECUTABLE = arc

#variables for testing
TEST_SRCS = tests/main.cpp tests/test_history.cpp tests/test_cache.cpp
TEST_LIBS = -lgtest -lgmock -pthread
TEST_OBJ = $(patsubst %.cpp, tbuild/%.o, $(subst tests/, , $(TEST_SRCS)))
TEST_EXEC = runtests

all: $(OBJ)
	@echo "CXX $(EXECUTABLE)"
	@$(CXX) $(CXX_FLAGS) $(OBJ) -o $(EXECUTABLE)
build/%.o: src/%.cpp
	mkdir -p ./build
	@$(CXX) $(CXX_FLAGS) -c -o $@ $<
tests: $(TEST_OBJ)
	@echo "CXX $(TEST_EXEC)"
	@$(CXX) $(CXX_FLAGS) $(TEST_OBJ) $(TEST_LIBS) -o $(TEST_EXEC)
tbuild/%.o: tests/%.cpp
	mkdir -p ./tbuild
	@$(CXX) $(CXX_FLAGS) -c -o $@ $<

.PHONY: clean mem tclean

clean:
	@rm -f build/*.o
	@rm -f $(EXECUTABLE)

tclean:
	@rm -f tbuild/*.o
	@rm -f $(TEST_EXEC)

mem:
	valgrind --leak-check=full --leak-resolution=med ./$(EXECUTABLE)
	
