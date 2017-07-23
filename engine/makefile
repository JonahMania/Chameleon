TARGET = engine.a

SRCDIR = src
BUILDDIR = obj
INCLUDEDIR = src/include
SRCEXT = cpp
OBJEXT = o
HDREXT = hpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

CC = g++
AR = ar
CFLAGS = -g -std=c++11
ARFLAGS = -rv
LIB = -lSDL2 -lSDL2_image

RM = rm -rf
MD = mkdir -p
CP = cp

all: $(basename $(TARGET))/$(TARGET) copy

#Link
$(basename $(TARGET))/$(TARGET): $(OBJECTS)
	@$(MD) $(basename $(TARGET))
	$(AR) $(ARFLAGS) $@ $^

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(LIB) -c -o $@ $<

#Copy
copy:
	@$(MD) $(basename $(TARGET))
	@$(CP) $(INCLUDEDIR)/*.$(HDREXT) $(basename $(TARGET))

#Clean
clean:
	$(RM) $(BUILDDIR)
	$(RM) $(basename $(TARGET))
