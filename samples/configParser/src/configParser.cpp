#include "configParser.hpp"

using json = nlohmann::json;

SDL_Color getColor(json j)
{
    SDL_Color ret;
    if(j.is_string() && j.get<std::string>().size() == 7 && j.get<std::string>()[0] == '#')
    {
        std::string color = j.get<std::string>();
        ret.r = std::stoi(color.substr(1,2), NULL, 16);
        ret.g = std::stoi(color.substr(3,2), NULL, 16);
        ret.b = std::stoi(color.substr(5,2), NULL, 16);
    }
    else if(j.is_object() && j["red"].is_number() && j["green"].is_number() && j["blue"].is_number())
    {
        ret.r = j["red"];
        ret.g = j["green"];
        ret.b = j["blue"];
    }
    else
    {
        ret.r = 0;
        ret.g = 0;
        ret.b = 0;
        std::cerr<<"Error: Bad color value setting to black"<<std::endl;
    }
    return ret;
}

//Returns a pointer to a new palette created from the given config file
Palette *getPaletteFromConfig(std::string configPath)
{
    std::ifstream jsonStream;
    json j;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    //Get all data from json before creating new object
    jsonStream = std::ifstream(configPath, std::ifstream::in);
    if(!jsonStream)
    {
        std::cerr<<"Error: Could not read json file '"<<configPath<<"'"<<std::endl;
        return NULL;
    }
    jsonStream >> j;

    if(j["baseColor"]["red"].is_number())
    {
        red = j["baseColor"]["red"].get<Uint8>();
    }else{
        std::cerr<<"Error: Palette file '"<<configPath<<"' is missing key 'red'"<<std::endl;
        return NULL;
    }
    if(j["baseColor"]["green"].is_number())
    {
        green = j["baseColor"]["green"];
    }else{
        std::cerr<<"Error: Palette file '"<<configPath<<"' is missing key 'green'"<<std::endl;
        return NULL;
    }
    if(j["baseColor"]["blue"].is_number())
    {
        blue = j["baseColor"]["blue"];
    }else{
        std::cerr<<"Error: Palette file '"<<configPath<<"' is missing key 'blue'"<<std::endl;
        return NULL;
    }

    return new Palette(red, green, blue);
}


Colorist *getColoristFromConfig(std::string configPath)
{
    std::ifstream jsonStream;
    json j;
    Colorist *colorist;
    //Get all data from json before creating new object
    jsonStream = std::ifstream(configPath, std::ifstream::in);
    if(!jsonStream)
    {
        std::cerr<<"Error: Could not read json file '"<<configPath<<"'"<<std::endl;
        return NULL;
    }
    jsonStream >> j;
    colorist = new Colorist();
    if(j["colorKeys"].is_array())
    {
        json array = j["colorKeys"].get<json>();

        for(json::iterator it = array.begin(); it < array.end(); it++ )
        {
            colorist->pushColorKey(getColor(*it));
        }
    }
    return colorist;
}
