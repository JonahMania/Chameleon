#ifndef _CONFIGPARSER_H_
#define _CONFIGPARSER_H_

#include "lib/json.hpp"
#include <fstream>
#include <sstream>

#include "lib/engine/Palette.hpp"
#include "lib/engine/Colorist.hpp"

class Palette *getPaletteFromConfig(std::string configPath);
class Colorist *getColoristFromConfig(std::string configPath);

#endif
