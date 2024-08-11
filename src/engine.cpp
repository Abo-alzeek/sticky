#include "../include/basic.h"

Engine::Engine(std::string level_path) {
    this->level = Level(level_path);

    std::cout << "SETTING MAP" << std::endl;

    for(int i = 0;i < (int)level.Map.size();i++) {
        for(int j = 0;j < (int)level.Map[i].size();j++) {      
            std::cout << " -> " << i << " " << j << "\n";      
            if(level.Map[i][j] == 0) continue;

            std::cout << "ONE\n";
    
            auto e = m_entities.addEntity(&tileTag); 
            std::cout << "ONE\n";
            e->cCollision = std::make_shared<CCollision>(sf::Vector2f(j * 64.0, i * 64.0), 64.0, 64.0);
            std::cout << "ONE\n";
            e->cTextrue = std::make_shared<CTexture>( m_resources.sprites[ level.Map[i][j] ]);
            std::cout << "ONE\n";
            e->cTextrue->sprite.setPosition(j*64, i*64);
            std::cout << "ONE\n";
        }
    }

    std::cout << "GOOD MAP" << std::endl;
    // // making stickman
    // e = m_entities.addEntity(&stickmanTag);
    // e->cAnimation = std::make_shared<CAnimation>();
    
    // e->cTransform = std::make_shared<CTransform>();
    // e->cTransform->pos = sf::Vector2f(level.spawinigPoints.back().first * 64.0, level.spawinigPoints.back().second * 64.0);
    
    // e->cTextrue = std::make_shared<CTexture>( m_resources.textures[1] );
    // e->cTextrue->sprite.setTexture(e->cTextrue->texture);
    // e->cTextrue->sprite.setTextureRect(sf::IntRect(0, 0, 40, 113));
    // e->cTextrue->sprite.setPosition(e->cTransform->pos);
    // e->cTextrue->sprite.setOrigin(e->cTextrue->sprite.getGlobalBounds().width/2.0, e->cTextrue->sprite.getGlobalBounds().height/2.0);
    
    // e->cInput = std::make_shared<CInput>();
    
    // e->cCollision = std::make_shared<CCollision>(e->cTransform->pos, e->cTextrue->sprite.getGlobalBounds().width, e->cTextrue->sprite.getGlobalBounds().height);
    // e->cCollision->boundingBox.setOrigin(e->cCollision->boundingBox.getGlobalBounds().width/2.0, e->cCollision->boundingBox.getGlobalBounds().height/2.0);


    // skeletal creation
    auto e = m_entities.addEntity(&skeletalTag);
    e->cBones = std::make_shared<CBones>();
    e->cBones->makeHumanSkeleton(70, 35, 37, 35, 40, 25, 20);

    e->cState = std::make_shared<CState>();
    e->cState->state = 0;
    e->cAnimation = std::make_shared<CAnimation>();
    e->cAnimation->setAnimation(this->m_resources.animations[e->cAnimation->currentAnimation], 1);
    e->cInput = std::make_shared<CInput>();

    e->cTransform = std::make_shared<CTransform>();

    std::cout << "EVERY THING IS DONE HERE" << std::endl;
}

Engine::~Engine() {
    ;
}

void Engine::run(sf::RenderWindow &window) {
    while(running) {
        m_entities.update();

        handleInput(window);
        std::cout << "ONE\n";
        update();
        // checkCollisions();        
        render(window);

        std::cout << "ONE\n";

        for(auto e : m_entities.getEntities()) {
            if(e->cState != NULL) {
                e->cState->lastFrameState = e->cState->state;
            }
        }

        m_currentFrame++;
    }    
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
                                // e->cAnimation->setAnimation(this->m_resources.animations[ANIMATIONS::RUN], 1);
                                // e->cAnimation->currentAnimation = ANIMATIONS::RUN;
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
    // handling input
    for(auto e : m_entities.getEntities()) {
        if(e->cState != NULL) {
            if(e->cState->state && (e->cState->state != e->cState->lastFrameState)) {
                e->cTransform->velocity.x = (e->cState->state / abs(e->cState->state)) * 7.0;
                e->cAnimation->setAnimation(this->m_resources.animations[abs(e->cState->state)], e->cState->state);
            }
            else if(!e->cState->state){
                e->cTransform->velocity.x = 0;
                e->cAnimation->setAnimation(this->m_resources.animations[abs(e->cState->state)], e->cState->state);
            }
        }
    }

    // update movements
    for(auto e : m_entities.getEntities()) {
        if(e->cTransform != NULL) {
            e->cTransform->velocity += e->cTransform->gravity;
            e->cTransform->pos += e->cTransform->velocity;
            e->cBones->moveBone(0, Point(e->cTransform->velocity.x, e->cTransform->velocity.y));
            // e->cCollision->boundingBox.setPosition(e->cTransform->pos);
        }
    }

    // update animations
    for(auto e : m_entities.getEntities()) {
        if(e->cAnimation != NULL) {
            e->cAnimation->playAnimation(e->cAnimation->moves, *e->cBones);
        }
    }

    // update sounds
}

int checkCollision(sf::RectangleShape rect1, sf::RectangleShape rect2) {
    int w1 = rect1.getGlobalBounds().width;
    int h1 = rect1.getGlobalBounds().height;
    rect1.setOrigin(w1/2.0, h1/2.0);
    int x1 = rect1.getPosition().x;
    int y1 = rect1.getPosition().y;

    int w2 = rect2.getGlobalBounds().width;
    int h2 = rect2.getGlobalBounds().height;
    rect2.setOrigin(w2/2.0, w2/2.0);
    int x2 = rect2.getPosition().x;
    int y2 = rect2.getPosition().y;

    if(abs(x1 - x2) <= (w1/2.0 + w2/2.0)) {
        if(abs(y1 - y2) <= (h1/2.0 + h2/2.0)) {
            return 2;
        }
    }

    return 0;
}

void Engine::checkCollisions() {
    // no collision between characters when no combat
    // collision is between characters and suroundings
    for(auto stickman : m_entities.getEntities(stickmanTag)) {
        bool isCollision = false;
        for(auto tile : m_entities.getEntities(tileTag)) {
            if(stickman->cCollision == NULL) continue;
            
            if(checkCollision(stickman->cCollision->boundingBox, tile->cCollision->boundingBox) == 2) { // 1 left, 2 bottom, 3 right, 4 above, 0 no collision
                stickman->cTransform->gravity = {0, 0};
                stickman->cTransform->velocity.y = 0;
                stickman->cTransform->pos.y = tile->cCollision->boundingBox.getPosition().y - (stickman->cCollision->boundingBox.getGlobalBounds().height/2.0);
                stickman->cTextrue->sprite.setPosition(stickman->cTransform->pos);
                stickman->cCollision->boundingBox.setPosition(stickman->cTransform->pos);
                isCollision = true;
            }

            // if(stickman->cCollision->boundingBox.getGlobalBounds().width/2.0 + stickman->cTransform->pos.x >= tile->cCollision->boundingBox.getGlobalBounds().width / 2.0 - tile->cCollision->boundingBox.getPosition().x) {
            //     stickman->cTransform->pos.x = (tile->cCollision->boundingBox.getGlobalBounds().width / 2.0 - tile->cCollision->boundingBox.getPosition().x) - stickman->cCollision->boundingBox.getGlobalBounds().width/2.0;
            //     stickman->cTextrue->sprite.setPosition(stickman->cTransform->pos);
            //     stickman->cCollision->boundingBox.setPosition(stickman->cTransform->pos);
            // }
            // if(stickman->cCollision->boundingBox.getGlobalBounds().width/2.0 - stickman->cTransform->pos.x <= tile->cCollision->boundingBox.getGlobalBounds().width / 2.0 + tile->cCollision->boundingBox.getPosition().x) {
            //     stickman->cTransform->pos.x = (tile->cCollision->boundingBox.getGlobalBounds().width / 2.0 + tile->cCollision->boundingBox.getPosition().x) + stickman->cCollision->boundingBox.getGlobalBounds().width/2.0;
            //     stickman->cTextrue->sprite.setPosition(stickman->cTransform->pos);
            //     stickman->cCollision->boundingBox.setPosition(stickman->cTransform->pos);
            // }
        }

        if(!isCollision) stickman->cTransform->gravity = {0, 0.2};
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

    for(auto &e : m_entities.getEntities(skeletalTag)) {
        for(auto &b : e->cBones->bones) {
            b.draw(window);
        }
    }

    window.display();
}


/*
cout
*/