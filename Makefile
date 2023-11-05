ifndef config
  config=debug
endif

CC=g++ -std=c++23
SRC=$(wildcard src/*.cpp) 
OBJ=$(SRC:.cpp=.o)
LINKS=
INCLUDE=-I src/include
CFLAGS= -Wall
EXEC=prog.exe

ifeq ($(config), debug)
TARGETDIR = bin/Debug
TARGET = $(TARGETDIR)/prog.exe
else ifeq ($(config),release)
CC+=-o3
TARGETDIR = bin/Release
TARGET = $(TARGETDIR)/prog.exe
CFLAGS +=-s 
endif


all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) -o $@ $(INCLUDE) $^ $(LINKS) $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ $(INCLUDE) -c $< $(LINKS) $(CFLAGS)

clean:
	rm src/*.o ${TARGETDIR}/*.exe