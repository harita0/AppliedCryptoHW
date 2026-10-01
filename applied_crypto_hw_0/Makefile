CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall -I../6.3.0/include -w
SRC := main.cpp \
       modular_arithmetic.cpp \
	   rsa.cpp \
	   elgamal.cpp \
	   diffie_hellman_key_exchange.cpp
	   
OBJ := $(SRC:.cpp=.o)
TARGET := myprogram
LIBS := -L../6.3.0/lib -lgmpxx -lgmp

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)