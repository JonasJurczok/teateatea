SOURCES=tea_tcursor.c tea_pack.c teateatea.c
TARGET=teateatea.so
TESTFILE=test.lua

SRCDIR=src
OBJDIR=obj

ifdef LUAPKG
	PREFIX=$(shell pkg-config --variable=prefix $(LUAPKG))
	LUA_LIBDIR=$(shell pkg-config --variable=INSTALL_CMOD $(LUAPKG))
	LUA_INCDIR=$(shell pkg-config --cflags $(LUAPKG))
	LUA=$(LUAPKG)
else
	PREFIX?=/usr/local
	LUA_LIBDIR?=$(PREFIX)/lib/lua/5.1
	LUA_INCDIR?=-I$(PREFIX)/include/luajit-2.0
	LUA?=$(PREFIX)/bin/luajit
endif

CCOPT=-O3 -Wall -fPIC $(CFLAGS) $(LUA_INCDIR)
LDOPT=-shared $(LDFLAGS)
CHMOD=755

SRC=$(addprefix $(SRCDIR)/, $(SOURCES))
OBJ=$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

ifeq ($(CC), clang)
	LDOPT+= -undefined dynamic_lookup
endif


all: build

build: $(TARGET)

obj:
	mkdir -p obj

$(TARGET): $(OBJ)
	$(CC) $(LDOPT) $(OBJ) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c obj
	$(CC) -c $(CCOPT) $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)

install: $(TARGET)
	mkdir -p $(LUA_LIBDIR)
	cp $(TARGET) $(LUA_LIBDIR)/$(TARGET)
	chmod $(CHMOD) $(LUA_LIBDIR)/$(TARGET)

test: $(TARGET)
	$(LUA) $(TESTFILE)

.PHONY: all clean build install test
