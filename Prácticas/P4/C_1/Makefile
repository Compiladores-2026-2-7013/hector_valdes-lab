CXX = g++
CXXFLAGS = -Wno-deprecated-register -O0 -std=c++17 -Wall -g

EXE = c1_parser

all: $(EXE)

$(EXE): Parser.cpp Lexer.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

Lexer.cpp: lexer.ll Parser.hpp
	flex -o $@ $<

Parser.cpp Parser.hpp: parser.yy
	bison -d $<

clean:
	rm -rf Lexer.cpp Parser.hpp Parser.cpp $(EXE)
