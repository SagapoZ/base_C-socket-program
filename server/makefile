CC=arm-linux-gcc

C_SOURCE=$(wildcard src/*.c)
TARGET=bin/project
INCLUDE_PATH=-I ins/
LIB_PATH=-lpthread
$(TARGET):$(C_SOURCE)
	$(CC) $^ -o $@ $(INCLUDE_PATH) $(LIB_PATH)

.PHONY:clean
	
clean:
	$(RM) $(TARGET)
