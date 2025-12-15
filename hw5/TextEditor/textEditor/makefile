CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = myapp
SOURCE = main.cpp


all: $(TARGET)


$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)


clean:
	rm -f $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
