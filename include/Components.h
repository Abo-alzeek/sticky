#ifndef Components_h_
#define Components_h_

#include "basic.h"

struct Bone {

    Bone() {
        ;
    }
    ~Bone() {
        ;
    }

    sf::Vector2f p1, p2;
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
            c1.setRadius(radius);
            c1.setOrigin(radius, radius);
            c1.setPosition(p1.x, p1.y);
            c1.setFillColor(sf::Color(0, 0, 0, 255));

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


class CInput {
public:
    int idx = 1;
    int angle = 0;

    bool screen = false;

	CInput();
    ~CInput();
};

class CState {
public:
    int state;
    int lastFrameState;
    int toUpdate;
    int lastState;

    int hp;
    
    sf::Vector2f position;

    const int INF = 2e9;

    CState();
    ~CState();
    void update();
};

class CBones {
public:
    std::vector< Bone > bones;
    std::vector< std::pair<int, float> > subMoves;
    std::vector< std::vector<std::pair<int, float>> > moves;
    int remaining = 0, idx = 0;

    CBones();
    ~CBones();

    void update(int);
    void setBonePosition(int, sf::Vector2f);
    void printState();
    void moveBone(int, sf::Vector2f);
    void rotateBone(int, float);
    void setBoneAngle(int, float);
    void addBone(sf::Vector2f, sf::Vector2f, int, int, float, int);
    void makeHumanSkeleton(float, float, float, float, float, float, float, float);
};

class CAnimation {
    public:
    float frameTL;
    int invert = 1;
    sf::Clock timer;
    int currentFrame, framesCount;
    int currentAnimation, forceFrameOut;
    std::vector< std::vector<std::pair<int, float>> > moves;

    CAnimation();
    ~CAnimation();
    void setAnimation(anime, int);
    void playAnimation(std::vector< std::vector<std::pair<int, float>> > &, CBones &, std::shared_ptr<CState> &);
};

class CHealth {
public:
    int HP = 0;
    sf::RectangleShape healthBar, health;

    void updateHealth(int upd = -7);
    void setBarsPosition(sf::Vector2f);

    CHealth();
    ~CHealth();
    CHealth(int, sf::Vector2f);
};

#endif
