TARGET=restserver
SRC=$(shell find . -type f -name "*.cpp")
OBJ=$(SRC:.cpp=.o)
INC=-Iinclude
LIBS=-lboost_system -lcrypto -lssl -lcpprest

build: $(OBJ)
	g++ -std=c++11 $(OBJ) $(LIBS) -o $(TARGET)

.cpp.o:
	g++ -std=c++11 -c $< $(INC) -o $@

.PHONY:clean
clean:
	rm -rf $(OBJ)
	rm -rf $(TARGET)
