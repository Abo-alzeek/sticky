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
#include <memory>

#include "resources.h"
#include "game.h"
#include "miniLevel.h"
#include "Components.h"
#include "Entity.h"
#include "EntityManager.h"
#include "button.h"
#include "menu.h"
#include "Level.h"
#include "engine.h"

#define FPS 60
#define HEIGHT 768
#define WIDTH 1280
#define PI acos(-1)
// #define float double

void test();
void test2();
void test3();
void test4();
std::string pobierzAktualnyCzas();
std::string convertSecondsToMinutes(float);
std::string convertIntToString(int);

#endif
