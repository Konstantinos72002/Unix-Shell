# CC := g++
# CFLAGS := -Wall -g
# TARGET := mysh

# # $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
# SRCS := $(wildcard *.cpp)
# # $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
# OBJS := $(patsubst %.cpp,%.o,$(SRCS))

# all: $(TARGET)
# $(TARGET): $(OBJS)
# 	$(CC) -o $@ $^
# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $<
# clean:
# 	rm -rf $(TARGET) *.o
	
# .PHONY: all clean
SRC_DIR := Sources
OBJ_DIR := Objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

mysh: $(OBJ_FILES)
	g++  -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++  -c -o $@ $<