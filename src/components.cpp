#include "../include/basic.h"

CTransform::CTransform() {
    ;
}

CTransform::~CTransform() {
    ;
}

void CTransform::move() {
    ;
}

CCollision::CCollision() {
    ;
}

CCollision::~CCollision() {
    ;
}


CCollision::CCollision(sf::Vector2f topLeft, float width, float height) {
    this->boundingBox.setPosition(topLeft);
    this->boundingBox.setSize(sf::Vector2f(width, height));

}

CTexture::~CTexture() {
    ;
}

CTexture::CTexture() {
    ;
}

CTexture::CTexture(sf::Sprite& s) {
    this->sprite = s;
}

CTexture::CTexture(sf::Texture &t) {
    this->texture = t;
    this->sprite.setTexture(texture);
}

CTexture::CTexture(std::string path) {
    if(!this->texture.loadFromFile(path)) {
        std::cout << "TEXTURE { " << path << " } CANNOT BE LOADED!!!" << std::endl;
        return;
    }

    this->sprite.setTexture(texture);
}

CInput::CInput() {
    ;
}

CInput::~CInput() {
    ;
}

CAnimation::CAnimation() {
    currentAnimation = STICKMAN_IDL;

    currentFrame = 0;
    framesCount = 10;
    textureIdx = 1;

    frameX = frameY = 0;
    frameW = 40;
    frameH = 113;
    frameTL = 0.12;

    timer.restart();
}

CAnimation::~CAnimation() {
    ;
}

sf::Sprite CAnimation::playAnimation(std::vector<sf::Texture> &textures) {
    if( timer.getElapsedTime().asSeconds() >= frameTL ) {
        currentFrame = (currentFrame + 1) % framesCount;
        timer.restart();
    }

    sf::Sprite s(textures[textureIdx], sf::IntRect(frameX + frameW * currentFrame + (int)(0.5 * currentFrame), frameY, frameW, frameH));
    s.setScale(invert, 1);
    return s;
}

void CAnimation::setAnimation(anime a, int in) {
    // set timer and currentframe to zero
    this->timer.restart();
    this->currentFrame = 0;
    
    // set frames count
    this->framesCount = a.framesCount;
    
    // set textureIdx
    this->textureIdx = a.textureIdx;
    
    // set frame(x, y, w, h)
    this->frameX = a.frameX;
    this->frameY = a.frameY;
    this->frameW = a.frameW;
    this->frameH = a.frameH;
    
    // set frame time
    this->frameTL = a.frameTL;
    
    // set enum
    this->currentAnimation = a.animation;

    // set invert
    if(in) this->invert = in;
}

CBones::CBones() {
    // std::cout << "KOS" << std::endl;
    ;
}

CBones::~CBones() {
    // std::cout << "KOS" << std::endl;
    ;
}

void CBones::addBone(Point p1, Point p2, int p, int side, float length, int isHead) {
    Bone b;

    if(p > -1) {
        if(side == 1) b.p1 = this->bones[p].p1;
        else          b.p1 = this->bones[p].p2;

        if(isHead) length *= -1;
        b.p2.x = b.p1.x;
        b.p2.y = b.p1.y + length;
        
        this->bones[p].children.push_back( (int)this->bones.size() );
    }
    else {
        b.p1 = p1;
        b.p2 = p2;
    }

    b.parent = p;
    b.length = abs(length);
    b.side = side;
    
    if(isHead == 1) b.init(isHead, length);
    else b.init(0);

    this->bones.push_back(b);
}

void CBones::makeHumanSkeleton(float backBone = 70.0, float arm = 35.0, float hand = 27.0, float leg = 35.0, float foot = 30.0, float neck = 10.0, float head = 10.0) {
    Point p1, p2, no;
    p1.x = 600;
    p1.y = 300;
    p2.x = p1.x;
    p2.y = p1.y + backBone;
    no.x = -1;
    no.y = -1;

    this->addBone(p1, p2, -1, -1, backBone, 0);
    this->addBone(no, no, 0, 1, arm, 0);
    this->addBone(no, no, 0, 1, arm, 0);
    this->addBone(no, no, 1, 2, hand, 0);
    this->addBone(no, no, 2, 2, hand, 0);
    this->addBone(no, no, 0, 2, leg, 0);
    this->addBone(no, no, 0, 2, leg, 0);
    this->addBone(no, no, 5, 2, foot, 0);
    this->addBone(no, no, 6, 2, foot, 0);
    this->addBone(no, no, 0, 1, neck, 0);
    this->rotateBone(9, 180);
    this->addBone(no, no, 9, 2, head, 1);
}

void CBones::moveBone(int id, Point v) {
    this->bones[id].p1.x += v.x;
    this->bones[id].p1.y += v.y;

    this->bones[id].p2.x += v.x;
    this->bones[id].p2.y += v.y;

    this->bones[id].update();
    this->update(id);
}

void CBones::rotateBone(int id, float deg) {
    float x = this->bones[id].p2.x - this->bones[id].p1.x;
    float y = (this->bones[id].p2.y - this->bones[id].p1.y) * -1;
    float r = this->bones[id].length;

    if(abs(x) < 1e-4) x = 0;
    if(abs(y) < 1e-4) y = 0;
    
    float X = r * cos(atan2(y, x) + PI / 180.0 * deg);
    float Y = r * sin(atan2(y, x) + PI / 180.0 * deg);

    if(abs(X) < 1e-4) X = 0;
    if(abs(Y) < 1e-4) Y = 0;

    x = X;
    y = -Y;

    x += this->bones[id].p1.x;
    y += this->bones[id].p1.y;
    
    this->bones[id].p2.x = x;
    this->bones[id].p2.y = y;

    this->bones[id].R.rotate(-deg);
    this->bones[id].update();

    this->update(id);
}

void CBones::update(int u) {
    bones[u].update();

    for(auto v : bones[u].children) {
        Point move ;

        if(bones[v].side == 1) {
            move.x = bones[u].p1.x - bones[v].p1.x;
            move.y = bones[u].p1.y - bones[v].p1.y;
            bones[v].p1 = bones[u].p1;
        }
        else {
            move.x = bones[u].p2.x - bones[v].p1.x;
            move.y = bones[u].p2.y - bones[v].p1.y;
            bones[v].p1 = bones[u].p2;
        }

        bones[v].p2.x += move.x;
        bones[v].p2.y += move.y;


        this->update(v);
    }
}

void CBones::printState() {
    for(int i = 0;i < (int)bones.size();i++) {
        std::cout << i << ": " << atan2(bones[i].p2.y - bones[i].p1.y, bones[i].p2.x - bones[i].p1.x) * 180.0 / PI << std::endl;
    }
    std::cout << "-----" << std::endl;
}
