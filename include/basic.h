#ifndef BASIC_H_
#define BASIC_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <functional>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp> 
#include "json.hpp"

#include "resources.h"
#include "game.h"
#include "miniLevel.h"
#include "Components.h"
#include "Entity.h"
#include "EntityManager.h"
#include "button.h"
#include "listener.h"
#include "menu.h"
#include "Level.h"
#include "engine.h"

using json = nlohmann::json;
typedef websocketpp::client<websocketpp::config::asio_client> client;

#define FPS 60
// #define HEIGHT 1080
// #define WIDTH 1920
#define HEIGHT 768
#define WIDTH 1280
#define PI acos(-1)

enum STICKPARTS {
    WAIST, BACK, RIGHT_ARM, LEFT_ARM, RIGHT_HAND, LEFT_HAND, RIGHT_LEG, LEFT_LEG, RIGHT_FOOT, LEFT_FOOT, NECK, HEAD
};

enum Animations {
    STICKMAN_IDLE, STICKMAN_RUN, STICKMAN_PUNCH, STICKMAN_DAMAGE, STICKMAN_DIE, STICKMAN_JUMP
};

enum textures {
    NOTHING = 0, GRAVEL = 1, WATER_SURFACE, DEEP_WATER, BRICK_WALL, STONE_WALL, BOX, SPAWNING_POINT, GRASS, DIRT, STICK_BODY, STICK_PART
};

enum Backgrounds {
    BLUESTANDARD, MOONLIGHT, WHITECLOUDYSKY1, WHITECLOUDYSKY2
};

#endif
