CC = g++
CFLAGS = -std=c++11
SRCDIR = src
BUILDDIR = build
TARGET = MusicLibrary

SRCS := $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
	make

