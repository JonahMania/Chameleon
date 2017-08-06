TARGET = tileMapper

SRCDIR = src
BUILDDIR = obj
SRCEXT = cpp
OBJEXT = o

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

CC = g++
CFLAGS = -g -std=c++11
LIB = -lSDL2 -lSDL2_image

RM = rm -f
MD = mkdir -p
CP = cp -r

all: copy $(TARGET)

#Link
$(TARGET): $(OBJECTS) src/lib/engine/engine.a
	$(CC) $(LIB) -o $@ $^

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

#Copy
copy:
	@$(MD) ./src/lib
	$(CP) ../../engine/engine ./src/lib/engine

#Clean
clean:
	$(RM) -r $(BUILDDIR)
	$(RM) $(TARGET)
	$(RM) -r ./src/lib/engine

#Remake
remake: clean copy $(TARGET)
