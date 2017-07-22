NAME = colorGen
SRC = src/main.cpp\
	src/colorist/Palette.cpp\
	src/colorist/Palette.hpp\
	src/colorist/Colorist.cpp\
	src/colorist/Colorist.hpp\
	src/template/Template.cpp\
	src/template/Template.hpp\
	src/configParser/configParser.cpp\
	src/configParser/configParser.hpp\
	src/utils/pixelAccess.cpp\
	src/utils/pixelAccess.hpp\
	src/lib/json.hpp

OBJ = $(SRC:.cpp=.o)
RM = rm -f
CXXFLAGS= -g -std=c++11
all: $(OBJ)
		g++ $(OBJ) -lSDL2 -lSDL2_image -o $(NAME) $(CXXFLAGS)

clean:
		-$(RM) src/*.o
		-$(RM) src/colorist/*.o
		-$(RM) src/configParser/*.o
