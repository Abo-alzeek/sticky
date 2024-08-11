#ifndef Components_h_
#define Components_h_

#include "basic.h"

struct Point {
    float x, y;

    Point() {
        ;
    }

    ~Point() {
        ;
    }
};

struct Bone {

    Bone() {
        ;
    }
    ~Bone() {
        ;
    }

    Point p1, p2;
    int side = 0;
    int parent = 0;
    float length = 0;
    std::vector<int> children;

    sf::CircleShape c1, c2;
    sf::RectangleShape R;

    // std::shared_ptr<CCollision> C1, C2, CR;

    void init(bool isHead, float radius = 4.0) {

        if(isHead) {
            c1.setRadius(radius);
            c1.setOrigin(radius, radius);
            c1.setPosition(p1.x, p1.y);
            c1.setFillColor(sf::Color(0, 0, 0, 255));
        }
        else {
            // C1 = std::make_shared<CCollision>();
            // C2 = std::make_shared<CCollision>();
            // CR = std::make_shared<CCollision>();

            c1.setRadius(radius);
            c1.setOrigin(radius, radius);
            c1.setPosition(p1.x, p1.y);
            c1.setFillColor(sf::Color(0, 0, 0, 255));
            // C1->boundingBox.setSize(sf::Vector2f());

            c2.setRadius(radius);
            c2.setOrigin(radius, radius);
            c2.setPosition(p2.x, p2.y);
            c2.setFillColor(sf::Color(0, 0, 0, 255));

            R = sf::RectangleShape(sf::Vector2f(2 * radius, abs(p1.y - p2.y)));
            R.setOrigin(radius, 0);
            R.setPosition(p1.x, p1.y);
            R.setFillColor(sf::Color(0, 0, 0, 255));
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(R);
        window.draw(c1);
        window.draw(c2);
    }

    void update() {
        c1.setPosition(p1.x, p1.y);
        c2.setPosition(p2.x, p2.y);
        R.setPosition(p1.x, p1.y);
    }
};

class CTransform {
public:
	sf::Vector2f pos = {0, 0};
	sf::Vector2f velocity = {0, 0};
    sf::Vector2f gravity = {0, 0};

    CTransform();
    ~CTransform();
    void move();
};

enum Animations {
    STICKMAN_IDL, STICKMAN_RUN
};

class CCollision {
public:
	sf::RectangleShape boundingBox;
    CCollision();
	CCollision(sf::Vector2f, float, float);
    ~CCollision();
};

class CTexture {
    public:
    sf::Texture texture;
    sf::Sprite sprite;
    
    CTexture();
    CTexture(sf::Sprite &);
    CTexture(sf::Texture &);
    CTexture(std::string path);
    ~CTexture();
};

class CAnimation {
    public:
    sf::Clock timer;
    int currentAnimation;
    int currentFrame, framesCount, textureIdx;
    int frameX, frameY, frameW, frameH;
    float frameTL;
    int invert = 1;


    CAnimation();
    ~CAnimation();
    sf::Sprite playAnimation(std::vector<sf::Texture> &);
    void setAnimation(anime, int);
};

class CInput {
public:
    bool lastFrameRight = false;
    bool lastFrameLeft = false;
    bool movingRight = false;
    bool movingLeft = false;

    int idx = 1;
    int angle = 0;

    bool screen = false;

	CInput();
    ~CInput();
};

class CBones {
public:
    std::vector< Bone > bones;

    CBones();
    ~CBones();

    void update(int);
    void printState();
    void moveBone(int, Point);
    void rotateBone(int, float);
    void addBone(Point, Point, int, int, float, int);
    void makeHumanSkeleton(float, float, float, float, float, float, float);
};

#endif
