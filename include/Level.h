#ifndef Level_h_
#define Level_h_

#include "basic.h"

class Level {
public:
    std::vector< std::vector<int> > Map;
	int width; 
	int height; 
    int background;
	std::pair<int, int> topLeftVisible; 
	std::pair<int, int> bottomRightVisible;

    std::string levelName;
    std::vector< std::pair<int, int> > spawinigPoints;
    
    Level();
    Level(std::string path);
};

#endif