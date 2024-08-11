#include "../include/basic.h"

//---------------------------------------------------------------------------------------

const std::string Resources::graphicsDirectory = "res/images/";
const std::string Resources::fontsDirectory = "res/fonts/";
const std::string Resources::animationsDirectory = "res/Animations/";

//---------------------------------------------------------------------------------------

Resources::Resources() {
    loadTextures();
    setSprites();
    getAnimations();
    // getAnimations2();

    std::cout << "SPRITES ARE SET SUCCESSFULLY!" << std::endl;
}

//---------------------------------------------------------------------------------------

std::string Resources::getSkyWallpaper1() {
    return Resources::graphicsDirectory + "cloudySkyWallpaper_1.jpeg";
}

//---------------------------------------------------------------------------------------

std::string Resources::getSkyWallpaper2() {
    return Resources::graphicsDirectory + "cloudySkyWallpaper_2.jpeg";
}

//---------------------------------------------------------------------------------------

std::string Resources::getMoonlightWallpaper() {
    return Resources::graphicsDirectory + "Moonlight.jpeg";
}

//---------------------------------------------------------------------------------------

std::string Resources::getStickmanSpriteSheet() {
    return Resources::graphicsDirectory + "stickman_spritesheet.png";
    // w = 249, h = 695
}

//---------------------------------------------------------------------------------------

std::string Resources::getMenuBackgroundTexture()
{
    return Resources::graphicsDirectory + "backg1.jpg";
}

//---------------------------------------------------------------------------------------

std::string Resources::getMenuBackgroundFont()
{
    return Resources::fontsDirectory  + "BLOCKSS.otf";
}

//---------------------------------------------------------------------------------------

std::string Resources::getBackground1() {
    return Resources::graphicsDirectory + "backg1.jpg";
}

//---------------------------------------------------------------------------------------

std::string Resources::getTilesTexture() {
    return Resources::graphicsDirectory + "tilesheet.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getStickmanBody() {
    return Resources::graphicsDirectory + "stick_body_2.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getStickmanPart() {
    return Resources::graphicsDirectory + "stickPart2.png";
}

//---------------------------------------------------------------------------------------

void Resources::loadTextures() {
    std::cout << " -> LOADING TEXTURES..." << std::endl;
    sf::Texture temp;

    // tile sheet
    if(!temp.loadFromFile(getTilesTexture())) std::cout << "TILE SHEET NOT FOUND!!" << std::endl;
    else textures.push_back(temp);

    // stickman sheet
    if(!temp.loadFromFile(getStickmanSpriteSheet())) std::cout << "NO STICKMAN SHEET FOUND!!" << std::endl;
    else textures.push_back(temp);

    // background_1
    if(!temp.loadFromFile(getBackground1() )) std::cout << "No backgroun1 texture!!" << std::endl;
    else textures.push_back(temp);

    // moonlight
    if(!temp.loadFromFile(getMoonlightWallpaper() )) std::cout << "No backgroun1 texture!!" << std::endl;
    else textures.push_back(temp);

    // white sky 1
    if(!temp.loadFromFile(getSkyWallpaper1() )) std::cout << "No backgroun1 texture!!" << std::endl;
    else textures.push_back(temp);

    // white sky 2
    if(!temp.loadFromFile(getSkyWallpaper2() )) std::cout << "No backgroun1 texture!!" << std::endl;
    else textures.push_back(temp);

    // // stickman body
    // if(!temp.loadFromFile(getStickmanBody() )) std::cout << "NO STICKMAN BODY!!" << std::endl;
    // else textures.push_back(temp);

    // // stickman part
    // if(!temp.loadFromFile(getStickmanPart() )) std::cout << "NO STICKMAN PART!!" << std::endl;
    // else textures.push_back(temp);

    std::cout << " -- > texture: " << temp.getSize().x << " " << temp.getSize().y << std::endl;
}

//---------------------------------------------------------------------------------------

void Resources::setSprites() {
    std::cout << " -> SETTING SPRITES.." << std::endl;
    sf::Sprite semp;
    semp.setTexture(textures[0]);

    this->sprites.push_back(semp);

    // gravel
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(192, 64, 64, 64));

    // water surface
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(256, 0, 64, 64));

    // deap water
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(256, 64, 64, 64));

    // brick wall
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(192, 192, 64, 64));

    // stone wall
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(192, 256, 64, 64));

    // box
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(256, 320, 64, 64));

    // spawning point
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(704, 320, 64, 64));

    // grass 
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(0, 0, 64, 64));

    // dirt
    this->sprites.push_back(semp);
    this->sprites.back().setTextureRect(sf::IntRect(192, 0, 64, 64));

    // background_1
    semp.setTexture(textures[2]);
    this->backgrounds.push_back(semp);
    this->backgrounds.back().setScale( (float)WIDTH / backgrounds.back().getGlobalBounds().width, (float)HEIGHT / backgrounds.back().getGlobalBounds().height);

    // moonlight
    semp.setTexture(textures[3]);
    this->backgrounds.push_back(semp);
    this->backgrounds.back().setScale( (float)WIDTH / backgrounds.back().getGlobalBounds().width, (float)HEIGHT / backgrounds.back().getGlobalBounds().height);

    // white sky 1
    semp.setTexture(textures[4]);
    this->backgrounds.push_back(semp);
    this->backgrounds.back().setScale( (float)WIDTH / backgrounds.back().getGlobalBounds().width, (float)HEIGHT / backgrounds.back().getGlobalBounds().height);

    // white sky 2
    semp.setTexture(textures[5]);
    this->backgrounds.push_back(semp);
    this->backgrounds.back().setScale( (float)WIDTH / backgrounds.back().getGlobalBounds().width, (float)HEIGHT / backgrounds.back().getGlobalBounds().height);

    // // stickman body
    // sf::Sprite semp2;
    // semp2.setTexture(textures[6]);
    // semp = semp2;
    // this->sprites.push_back(semp);

    // // stickman part
    // sf::Sprite semp3;
    // semp3.setTexture(textures[7]);
    // semp = semp3;
    // this->sprites.push_back(semp);
}

//---------------------------------------------------------------------------------------

void Resources::getAnimations() {
    int fc;
    float ftl;

    anime a;
    std::fstream file;

    std::vector< std::pair<int, float> > temp;
    std::vector< std::vector< std::pair<int, float> > > movement;

    file.open(animationsDirectory + "bones_stickman_idle.txt");
    file >> fc >> ftl;
    
    a.framesCount = fc;
    a.frameTL = ftl;
    a.idx = 0;
    
    for(int i = 0;i < fc;i++) {
        int n; 
        file >> n;
        for(int j = 0;j < n;j++) {
            temp.emplace_back();
            file >> temp.back().first >> temp.back().second;
        }
        movement.push_back(temp);
        temp.clear();
    }

    a.movement = movement;
    animations.push_back(a);

    file.close();



    temp.clear();
    movement.clear();

    file.open(animationsDirectory + "bones_stickman_run.txt");
    file >> fc >> ftl;
    a.framesCount = fc;
    a.frameTL = ftl;
    a.idx = 1;

    for(int i = 0;i < fc;i++) {
        int n; 
        file >> n;
        for(int j = 0;j < n;j++) {
            temp.emplace_back();
            file >> temp.back().first >> temp.back().second;
            temp.back().second *= -1;
        }
        movement.push_back(temp);
        temp.clear();
    }

    a.movement = movement;
    animations.push_back(a);

    file.close();
}

void Resources::getAnimations2() {
    int n, tempN;
    std::fstream file;
    std::vector< std::pair<int, float> > anime;
    std::vector< std::vector< std::pair<int, float> > > tempVec;

    file.open(animationsDirectory + "bones_stickman_run.txt");
    file >> n;
    for(int i = 0;i < n;i++) {
        file >> tempN;
        for(int j = 0;j < tempN;j++) {
            anime.emplace_back();
            file >> anime.back().first >> anime.back().second;
        }

        tempVec.push_back(anime);
        anime.clear();
    }

    animations2.push_back(tempVec);
}
