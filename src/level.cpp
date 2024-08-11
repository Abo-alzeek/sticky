#include "../include/basic.h"

Level::Level() {
    ;
}

Level::Level(std::string path) {
    std::fstream file;
    file.open(path);

    file >> height;
    file >> width;

    Map.resize(height);
    for(int i = 0;i < height;i++) {
        Map[i].resize(width);
        for(int j = 0;j < width;j++) {
            file >> Map[i][j];
        }
    }

    file >> background;

    int spawn_num;
    file >> spawn_num;

    for(int i = 0;i < spawn_num;i++) {
        int x, y;
        file >> x >> y;
        spawinigPoints.push_back( {x, y} );
    }

    file.close();
}