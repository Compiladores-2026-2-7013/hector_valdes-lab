
# -- Project name
TARGET := compiler

# -- Toolchain ---
CXX      := clang++
CXXDEBUG := -g -Wall -Wextra -Wpedantic
CXXSTD   := -std=c++14
CXXFLAGS := -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD)

# -- Directories 
LEX_DIR := AL

CPPOBJ := main \
										Parser \
										$(LEX_DIR)\Lexer

SRC_FILES= $(addsuffix .cpp, $(CPPOBJ))
OBJS = $(addsuffix .o, $(CPPOBJ))

CLEANLIST = $(OBJS) $(TARGET)

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "LINKING FOR $@"
	@echo "Object $^"
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $(TARGET)"
	
clean:
	@echo "Removing artifects"
	rm -rf $(CLEANLIST)
