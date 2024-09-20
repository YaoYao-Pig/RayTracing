# 定义编译器和编译选项
CC = g++
CCFLAGS = -Wall -Wextra -I.

# 定义源文件和目标文件
SRCS = Shape.cpp main.cpp # 添加其他源文件
OBJS = $(SRCS:.cpp=.o)

# 可执行文件名
TARGET = RayTracing

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# 编译每个源文件
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 声明伪目标
.PHONY: all clean
