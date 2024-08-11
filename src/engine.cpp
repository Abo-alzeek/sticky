#include "../include/basic.h"

Engine::Engine(std::string level_path) {
    // this->level = Level(level_path);

    // for(int i = 0;i < (int)level.Map.size();i++) {
    //     for(int j = 0;j < (int)level.Map[i].size();j++) {            
    //         if(level.Map[i][j] == 0) continue;
    
    //         auto e = m_entities.addEntity(&tileTag); 
    //         e->cCollision = std::make_shared<CCollision>(sf::Vector2f(j * 64.0, i * 64.0), 64.0, 64.0);
    //         e->cTextrue = std::make_shared<CTexture>( m_resources.sprites[ level.Map[i][j] ]);
    //         e->cTextrue->sprite.setPosition(j*64, i*64);
    //     }
    // }

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
    e->cInput = std::make_shared<CInput>();
}

Engine::~Engine() {
    ;
}

void Engine::run(sf::RenderWindow &window) {
    while(running) {
        m_entities.update();

        handleInput(window);
        update();
        checkCollisions();        
        render(window);

        for(auto e : m_entities.getEntities()) {
            if(e->cInput != NULL) {
                e->cInput->lastFrameLeft = e->cInput->movingLeft;
                e->cInput->lastFrameRight = e->cInput->movingRight;
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
                        for(auto e : m_entities.getEntities(stickmanTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->movingLeft= true;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        for(auto e : m_entities.getEntities(stickmanTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->movingRight = true;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::Up:
                        for(auto e : m_entities.getEntities(skeletalTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->idx = (e->cInput->idx + 1) % 10;
                            }
                        }
                        break;
                    case sf::Keyboard::Down:
                        for(auto e : m_entities.getEntities(skeletalTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->idx = (e->cInput->idx - 1 + 10) % 10;
                            }
                        }
                        break;
                    case sf::Keyboard::Right:
                        for(auto e : m_entities.getEntities(skeletalTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->angle = (e->cInput->angle + 5) % 360;
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        for(auto e : m_entities.getEntities(skeletalTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->angle = (e->cInput->angle - 5 + 360) % 360;
                            }
                        }
                        break;
                    case sf::Keyboard::Space:
                        for(auto e : m_entities.getEntities(skeletalTag)) {
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
                        for(auto e : m_entities.getEntities(stickmanTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->movingLeft= false;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        for(auto e : m_entities.getEntities(stickmanTag)) {
                            if(e->cInput != NULL) {
                                e->cInput->movingRight = false;
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
        if(e->cInput != NULL) {
            // if(e->cInput->movingRight && !e->cInput->lastFrameRight) {
            //     e->cTransform->velocity.x = 7.0;
            //     e->cAnimation->setAnimation(this->m_resources.animations[Animations::STICKMAN_RUN], 1);
            // }
            // else if(e->cInput->movingLeft && !e->cInput->lastFrameLeft) {
            //     e->cTransform->velocity.x = -7.0;
            //     e->cAnimation->setAnimation(this->m_resources.animations[Animations::STICKMAN_RUN], -1);
            // }
            // else if( !e->cInput->movingRight && !e->cInput->movingLeft ){
            //     e->cTransform->velocity.x = 0;
            //     e->cAnimation->setAnimation(this->m_resources.animations[Animations::STICKMAN_IDL], 0);
            // }
            
            if(e->cInput->angle) {
                e->cBones->rotateBone(e->cInput->idx, e->cInput->angle);
                e->cInput->angle = 0;
            }
            if(e->cInput->screen) {
                e->cInput->screen = false;
                e->cBones->printState();
            }
        }
    }

    // update movements
    for(auto e : m_entities.getEntities()) {
        if(e->cTransform != NULL) {
            e->cTransform->velocity += e->cTransform->gravity;
            e->cTransform->pos += e->cTransform->velocity;
            e->cTextrue->sprite.setPosition(e->cTransform->pos);
            e->cCollision->boundingBox.setPosition(e->cTransform->pos);
        }
    }

    // update animations

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
