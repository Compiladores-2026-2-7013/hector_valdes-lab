# -- Project name
TARGET := analyzer

# -- Toolchain ---
CXX      := g++
CXXFLAGS := -g -Wall -I.

# -- Directories
SRC_DIR := src
HDR_DIR := headers

SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/Parser.cpp $(SRC_DIR)/Lexer.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# flex++ generates src/Lexer.cpp from src/lexer.ll
$(SRC_DIR)/Lexer.cpp: $(SRC_DIR)/lexer.ll
	flex++ -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run with the default test file
run: $(TARGET)
	./$(TARGET) prueba

# Run with valid/invalid test files
test: $(TARGET)
	@echo "=== valid_test1.txt ===";   ./$(TARGET) valid_test1.txt
	@echo "=== valid_test2.txt ===";   ./$(TARGET) valid_test2.txt
	@echo "=== invalid_test1.txt ==="; ./$(TARGET) invalid_test1.txt
	@echo "=== invalid_test2.txt ==="; ./$(TARGET) invalid_test2.txt

clean:
	rm -f $(SRC_DIR)/Lexer.cpp $(OBJS) $(TARGET)
