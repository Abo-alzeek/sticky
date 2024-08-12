#include "../include/basic.h"

Engine::Engine(std::string level_path) {
    this->level = Level(level_path);

    for(int i = 0;i < (int)level.Map.size();i++) {
        for(int j = 0;j < (int)level.Map[i].size();j++) {      
            if(level.Map[i][j] == 0) continue;

            auto e = m_entities.addEntity(&tileTag); 
            e->cCollision = std::make_shared<CCollision>(sf::Vector2f(j * 64.0, i * 64.0), 64.0, 64.0);
            e->cTextrue = std::make_shared<CTexture>( m_resources.sprites[ level.Map[i][j] ]);
            e->cTextrue->sprite.setPosition(j*64, i*64);
        }
    }

    // skeletal creation
    auto e = m_entities.addEntity(&skeletalTag);
    e->cInput = std::make_shared<CInput>();

    e->cState = std::make_shared<CState>();
    e->cState->state = 0;

    e->cAnimation = std::make_shared<CAnimation>();
    e->cAnimation->setAnimation(this->m_resources.animations[e->cState->state], 1);

    e->cTransform = std::make_shared<CTransform>();
    e->cTransform->pos.x = level.spawinigPoints[0].first;
    e->cTransform->pos.y = level.spawinigPoints[0].second;

    e->cCollision = std::make_shared<CCollision>();
    e->cCollision->boundingBox.setSize(sf::Vector2f(50, 170));
    e->cCollision->boundingBox.setOrigin(25, 85);
    e->cCollision->boundingBox.setPosition(e->cTransform->pos);

    e->cBones = std::make_shared<CBones>();
    e->cBones->makeHumanSkeleton(70, 35, 37, 35, 40, 25, 20);
    e->cBones->setBonePosition(0, Point(e->cTransform->pos.x, e->cTransform->pos.y - 40));
    
    // making another stickman
    e = m_entities.addEntity(&skeletalTag);
    e->cState = std::make_shared<CState>();
    e->cState->state = 0;

    e->cAnimation = std::make_shared<CAnimation>();
    e->cAnimation->setAnimation(this->m_resources.animations[e->cState->state], 1);

    e->cTransform = std::make_shared<CTransform>();
    e->cTransform->pos.x = level.spawinigPoints[0].first + 256;
    e->cTransform->pos.y = level.spawinigPoints[0].second;

    e->cCollision = std::make_shared<CCollision>();
    e->cCollision->boundingBox.setSize(sf::Vector2f(50, 170));
    e->cCollision->boundingBox.setOrigin(25, 85);
    e->cCollision->boundingBox.setPosition(e->cTransform->pos);

    e->cBones = std::make_shared<CBones>();
    e->cBones->makeHumanSkeleton(70, 35, 37, 35, 40, 25, 20);
    e->cBones->setBonePosition(0, Point(e->cTransform->pos.x, e->cTransform->pos.y - 40));

    std::cout << "EVERY THING IS DONE HERE" << std::endl;
}

Engine::~Engine() {
    ;
}

void Engine::run(sf::RenderWindow &window) {
    Listener listen;
    sf::Thread thread(listen.Run);
    thread.launch();

    while(running) {
        m_entities.update();

        handleInput(window);
        update();
        checkCollisions();
        render(window);

        for(auto e : m_entities.getEntities()) {
            if(e->cState != NULL) {
                e->cState->lastFrameState = e->cState->state;
            }
        }

        m_currentFrame++;
    }

    thread.terminate();
}

void Engine::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                this->running = false;
            break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        this->running = false;
                        break;
                    case sf::Keyboard::A:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cState->state = -1;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cState->state = 1;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::F:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cState->state = 2 * e->cAnimation->invert;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::Up:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cInput->idx = (e->cInput->idx + 1) % 10;
                            }
                        }
                        break;
                    case sf::Keyboard::Down:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cInput->idx = (e->cInput->idx - 1 + 10) % 10;
                            }
                        }
                        break;
                    case sf::Keyboard::Right:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cInput->angle = (e->cInput->angle + 5) % 360;
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cInput->angle = (e->cInput->angle - 5 + 360) % 360;
                            }
                        }
                        break;
                    case sf::Keyboard::Space:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                e->cInput->screen = true;
                            }
                        }
                    default:
                        break;
                }
            break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        this->running = false;
                        break;
                    case sf::Keyboard::A:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                if(e->cState->state == -1) e->cState->state = 0;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                if(e->cState->state == 1) e->cState->state = 0;
                                break;
                            }
                        }
                        break;
                    default:
                        break;
                }
            break;
        default:
            break;
        }
    }
}

/*

*/

void Engine::update() {
    // preUpdate
    for(auto e : m_entities.getEntities()) {
        if(e->cAnimation != NULL && !e->cAnimation->forceFrameOut) {
            e->cState->state = 0;
        }
    }

    // handling input
    for(auto e : m_entities.getEntities()) {
        if(e->cState != NULL) {
            if(e->cState->state != e->cState->lastFrameState) {
                int in = 1;
                if(e->cState->state) in = (e->cState->state / abs(e->cState->state));

                if(e->cState->state == 0) e->cTransform->velocity.x = 0;
                else if( abs(e->cState->state) == 1) e->cTransform->velocity.x = in * 7.0;
                else if( abs(e->cState->state) == 2) e->cTransform->velocity.x = 0;

                e->cAnimation->setAnimation(this->m_resources.animations[abs(e->cState->state)], (e->cState->state / (abs(e->cState->state) + (e->cState->state == 0))) - (e->cAnimation->invert / abs(e->cAnimation->invert)) * (e->cState->state != 0));
            }
            // std::cout << "STATE: " << e->cState->state << " " << e->cState->lastFrameState <<  "\n";
        }
    }

    // update movements
    for(auto e : m_entities.getEntities()) {
        if(e->cTransform != NULL) {
            e->cTransform->velocity += e->cTransform->gravity;            
            e->cTransform->pos += e->cTransform->velocity;
            e->cBones->moveBone(0, Point(e->cTransform->velocity.x, e->cTransform->velocity.y));
            e->cCollision->boundingBox.setPosition(e->cTransform->pos);
        }
    }

    // update animations
    for(auto e : m_entities.getEntities()) {
        if(e->cAnimation != NULL) {
            e->cAnimation->playAnimation(e->cAnimation->moves, *e->cBones, e->cState);
        }
    }

    // update sounds
}

int checkRectangularCollision(sf::RectangleShape rect1, sf::RectangleShape rect2) {
    int w1 = rect1.getGlobalBounds().width;
    int h1 = rect1.getGlobalBounds().height;
    int x1 = rect1.getPosition().x;
    int y1 = rect1.getPosition().y;
    float npx = x1 + w1/2.0;
    float npy = y1 + h1/2.0;
    rect1.setOrigin(w1/2.0, h1/2.0);
    rect1.setPosition(npx, npy);

    int w2 = rect2.getGlobalBounds().width;
    int h2 = rect2.getGlobalBounds().height;
    int x2 = rect2.getPosition().x;
    int y2 = rect2.getPosition().y;

    npx = x2 + w2/2.0;
    npy = y2 + h2/2.0;
    rect2.setOrigin(w2/2.0, h2/2.0);
    rect2.setPosition(npx, npy);

    if(abs(x1 - x2) <= (w1/2.0 + w2/2.0)) {
        if(abs(y1 - y2) <= (h1/2.0 + h2/2.0)) {
            return 2;
        }
    }

    return 0;
}

bool checkPointRectangleCollision(sf::RectangleShape rect, Point p) {
    int w = rect.getGlobalBounds().width;
    int h = rect.getGlobalBounds().height;

    rect.setOrigin(w/2.0, h/2.0);

    int x = rect.getPosition().x;
    int y = rect.getPosition().y;

    if( abs(p.x - x) < w/2.0 && abs(p.y - y) < h / 2.0) return true;
    return false;
}

void Engine::checkCollisions() {
    // no collision between characters when no combat
    // collision is between characters and suroundings
    for(auto stickman : m_entities.getEntities(skeletalTag)) {
        bool isCollision = false;
        for(auto tile : m_entities.getEntities(tileTag)) {
            if(stickman->cCollision == NULL) continue;
            
            if(checkRectangularCollision(stickman->cCollision->boundingBox, tile->cCollision->boundingBox) == 2) { // 1 left, 2 bottom, 3 right, 4 above, 0 no collision
                stickman->cTransform->gravity = {0, 0};
                stickman->cTransform->velocity.y = 0;
                stickman->cTransform->pos.y = tile->cCollision->boundingBox.getPosition().y - (stickman->cCollision->boundingBox.getGlobalBounds().height - stickman->cCollision->boundingBox.getOrigin().y);
                // stickman->cBones->moveBone(0, Point(0, (stickman->cCollision->boundingBox.getGlobalBounds().height / 2.0 + stickman->cCollision->boundingBox.getPosition().y) -  tile->cCollision->boundingBox.getPosition().y));
                stickman->cBones->setBonePosition(0, Point(stickman->cTransform->pos.x, stickman->cTransform->pos.y - 40));
                stickman->cCollision->boundingBox.setPosition(stickman->cTransform->pos);
                isCollision = true;
            }
        }

        for(auto stickman2 : m_entities.getEntities(skeletalTag)) {
            if(stickman2->id() == stickman->id()) continue;
            if( abs(stickman->cState->state) == 2 && checkPointRectangleCollision(stickman2->cCollision->boundingBox, stickman->cBones->bones[3].p2)) {
                std::cout << "STICKMAN WAS HIT" << std::endl;
            }
            if( abs(stickman2->cState->state) == 2 && checkPointRectangleCollision(stickman->cCollision->boundingBox, stickman2->cBones->bones[3].p2)) {
                std::cout << "STICKMAN WAS HIT" << std::endl;

            }
        }

        if(!isCollision) stickman->cTransform->gravity = {0, 1};
    }
}

void Engine::render(sf::RenderWindow &window) {
    window.clear(sf::Color(255, 255, 255, 255));

    // window.draw( this->m_resources.backgrounds[this->level.background] );

    for(auto e : m_entities.getEntities(tileTag)) {
        window.draw(e->cTextrue->sprite);
    }

    for(auto e : m_entities.getEntities(stickmanTag)) {
        window.draw(e->cTextrue->sprite);
    }

    for(auto &stickman : m_entities.getEntities()) {
        stickman->cCollision->boundingBox.setOutlineThickness(5);
        stickman->cCollision->boundingBox.setOutlineColor(sf::Color::Red);
        stickman->cCollision->boundingBox.setFillColor(sf::Color(255, 0, 0, 0));
        window.draw(stickman->cCollision->boundingBox);
    }

    for(auto &e : m_entities.getEntities(skeletalTag)) {
        for(auto &b : e->cBones->bones) {
            b.draw(window);
        }
    }

    window.display();
}


/*

*/