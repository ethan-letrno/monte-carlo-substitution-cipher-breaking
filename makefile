CXX = g++
CFLAGS = -std=c++11

TARGET = decryptsub

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CFLAGS) -o $(TARGET).exe $(TARGET).cpp