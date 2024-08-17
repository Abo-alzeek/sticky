#ifndef RESOURCES_H_
#define RESOURCES_H_
#include <string>

struct anime {
    int framesCount;
    float frameTL;
    int forceStopAfter;
    int idx;
    std::vector< std::vector<std::pair<int, float>> > movement;
};

class Resources
{
public:
    Resources();
    static std::string getMenuBackgroundTexture();
    static std::string getMenuBackgroundFont();
    static std::string getBackground1();
    static std::string getTilesTexture();
    static std::string getStickmanSpriteSheet();
    static std::string getSkyWallpaper1();
    static std::string getSkyWallpaper2();
    static std::string getMoonlightWallpaper();
    static std::string getRunningAnimation();
    static std::string getIdleAnimation();
    static std::string getStickmanBody();
    static std::string getStickmanPart();

    static const std::string graphicsDirectory;
    static const std::string fontsDirectory;
    static const std::string animationsDirectory;

    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite>  sprites;
    std::vector<sf::Sprite>  backgrounds;
    std::vector<anime>       animations;

    std::vector< std::vector< std::vector<std::pair<int, float>> > >animations2;

    void loadAnimation(std::string, int);
    void loadTextures();
    void setSprites();
    void getAnimations();
};

#endif