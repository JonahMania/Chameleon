#ifndef _CONFIGPARSER_H_
#define _CONFIGPARSER_H_

#include "../lib/json.hpp"
#include <fstream>
#include <sstream>

#include "../colorist/Palette.hpp"
#include "../colorist/Colorist.hpp"

class Palette *getPaletteFromConfig(std::string configPath);
class Colorist *getColoristFromConfig(std::string configPath);

#endif
