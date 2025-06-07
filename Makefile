CC = i686-w64-mingw32-g++
CFLAGS = -std=c++17 -Wall -Iinclude -I/usr/i686-w64-mingw32/include
LDFLAGS = -lws2_32 -liphlpapi -lssl -lcrypto -L/usr/i686-w64-mingw32/lib

SRC = main.cpp \
      attacks/volume.cpp \
      attacks/protocol.cpp \
      attacks/application.cpp \
      attacks/amplification.cpp \
      obfuscation.cpp \
      c2.cpp \
      utils.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = nltool.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)
