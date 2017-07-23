#ifndef _CONFIGPARSER_H_
#define _CONFIGPARSER_H_

#include "lib/json.hpp"
#include <fstream>
#include <sstream>

#include "lib/engine/engine.hpp"

class Palette *getPaletteFromConfig(std::string configPath);
class Colorist *getColoristFromConfig(std::string configPath);

#endif
