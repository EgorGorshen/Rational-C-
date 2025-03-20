CXX ?= c++
CXXFLAGS ?= -Wall -Wextra -std=c++20

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM = del
    RMDIR = rmdir /S /Q
else
    EXE =
    RM = rm -f
    RMDIR = rm -rf
endif

OBJ_DIR = build

OBJS = $(OBJ_DIR)/rational.o $(OBJ_DIR)/test_rational.o

all: test_rational$(EXE)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/rational.o: rational.cpp rational.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c rational.cpp -o $@

$(OBJ_DIR)/test_rational.o: test_rational.cpp rational.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c test_rational.cpp -o $@

test_rational$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

run-tests: test_rational$(EXE)
	./test_rational$(EXE)

clean:
	$(RM) test_rational$(EXE)
	$(RMDIR) $(OBJ_DIR)


