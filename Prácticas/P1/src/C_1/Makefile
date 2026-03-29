# Variables de compilación
CXX = g++
FLEX = flex++
CXXFLAGS = -Wall -std=c++11
TARGET = compiler

# Regla principal
all: $(TARGET)

# Generar código C++ a partir de Lex
Lexer.cpp: lexer.ll
	$(FLEX) lexer.ll

# Compilar el ejecutable
$(TARGET): Lexer.cpp main.cpp
	$(CXX) $(CXXFLAGS) Lexer.cpp main.cpp -o $(TARGET)

# Limpiar archivos generados
clean:
	rm -f Lexer.cpp $(TARGET)
