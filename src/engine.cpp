#include "../include/basic.h"

sf::Vector2f adjustPosition(sf::RectangleShape& movingRect, const sf::RectangleShape& staticRect) {
    // Get the bounds of the rectangles
    sf::FloatRect movingBounds = movingRect.getGlobalBounds();
    sf::FloatRect staticBounds = staticRect.getGlobalBounds();

    // Calculate the overlap on each axis
    float overlapLeft = movingBounds.left + movingBounds.width - staticBounds.left;
    float overlapRight = staticBounds.left + staticBounds.width - movingBounds.left;
    float overlapTop = movingBounds.top + movingBounds.height - staticBounds.top;
    float overlapBottom = staticBounds.top + staticBounds.height - movingBounds.top;

    // Find the minimum overlap to resolve the collision
    float minOverlapX = (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;
    float minOverlapY = (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;

    return sf::Vector2f(minOverlapX, minOverlapY);
}

void Engine::moveAll(std::shared_ptr<Entity> e, sf::Vector2f v) {
    if(e->cTransform != NULL) e->cTransform->pos = v;

    if(e->cCollision.size()) {
        for(int i = 0;i < (int)e->cCollision.size();i++) {
            e->cCollision[i]->boundingBox.setPosition(e->cTransform->pos.x, e->cTransform->pos.y + this->skeletonBoundingBoxesMargins[i]);
        }
    }

    if(e->cBones != NULL) e->cBones->setBonePosition(STICKPARTS::WAIST, v);

    if(e->cHealth != NULL) e->cHealth->setBarsPosition(sf::Vector2f(v.x - 50, v.y - 120));
}

void Engine::createSkeletonBoundingBoxes(std::shared_ptr<Entity> e) {
    for(int i=0; i<3; i++) {
        e->cCollision.emplace_back();
        e->cCollision.back() = std::make_shared<CCollision>();
        e->cCollision.back()->boundingBox.setSize(this->skeletonBoundingBoxes[i]);
        e->cCollision.back()->boundingBox.setOrigin(this->skeletonBoundingBoxes[i].x / 2.0, this->skeletonBoundingBoxes[i].y / 2.0);
        e->cCollision.back()->boundingBox.setPosition(e->cTransform->pos.x, e->cTransform->pos.y + this->skeletonBoundingBoxesMargins[i]);
        
        e->cCollision.back()->boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
        e->cCollision.back()->boundingBox.setOutlineColor(this->skeletonBoxesColors[i]);
        e->cCollision.back()->boundingBox.setOutlineThickness(2);
    }
}

void Engine::spawnStickman(bool input, bool texture, bool collision, bool animation, bool transform, bool bones, bool state, bool health, int idx) {
    auto e = m_entities.addEntity(&skeletalTag);
    
    if(input) e->cInput = std::make_shared<CInput>();

    if(state) {
        e->cState = std::make_shared<CState>();
        e->cState->state = 0;
    }

    if(animation) {
        e->cAnimation = std::make_shared<CAnimation>();
        e->cAnimation->setAnimation(this->m_resources.animations[e->cState->state], 1);
    }

    if(transform) {
        e->cTransform = std::make_shared<CTransform>();
        e->cTransform->pos.x = level.spawinigPoints[idx].first;
        e->cTransform->pos.y = level.spawinigPoints[idx].second;
    }

    if(collision) createSkeletonBoundingBoxes(e);

    if(bones) {
        e->cBones = std::make_shared<CBones>();
        e->cBones->makeHumanSkeleton(25, 45, 35, 37, 35, 40, 25, 20);
        e->cBones->setBonePosition(0, e->cTransform->pos);
    }

    if(health) {
        e->cHealth = std::make_shared<CHealth>(100, e->cBones->bones[STICKPARTS::HEAD].p1 + sf::Vector2f(0, -25));
    }
}

Engine::Engine(std::string level_path) {
    this->level = Level(level_path);

    std::fstream f;
    f.open("something.txt");
    std::string player;
    f >> player;

    std::cout << "THE PLAYER IS: " << player << std::endl;

    f.close();

    // INITIALIZING MAP LEVEL
    for(int i = 0;i < (int)level.Map.size();i++) {
        for(int j = 0;j < (int)level.Map[i].size();j++) {      
            if(level.Map[i][j] == 0) continue;

            auto e = m_entities.addEntity(&tileTag); 
            e->cCollision.push_back(std::make_shared<CCollision>(sf::Vector2f(j * 64.0, i * 64.0), 64.0, 64.0));
            e->cTextrue = std::make_shared<CTexture>( m_resources.sprites[ level.Map[i][j] ]);
            e->cTextrue->sprite.setPosition(j*64, i*64);
        }
    }

    // skeletals creation

    if(player == "player1") {
        this->spawnStickman(1, 0, 1, 1, 1, 1, 1, 1, 0);
        this->spawnStickman(0, 0, 1, 1, 1, 1, 1, 1, 1);
    }
    else {
        this->spawnStickman(0, 0, 1, 1, 1, 1, 1, 1, 0);
        this->spawnStickman(1, 0, 1, 1, 1, 1, 1, 1, 1);
    }

    std::cout << "EVERY THING IS DONE HERE" << std::endl;
}

Engine::~Engine() {
    ;
}

void Engine::run(sf::RenderWindow &window) {
    sf::Thread thread(this->listen.Run);
    thread.launch();
 
    while(running) {
        m_entities.update();

        handleInput(window);
        update();
        checkCollisions(window);
        render(window);

        m_currentFrame++;

        if (this->listen.connected == 0) {
            //thread.terminate();
            //thread = sf::Thread(this->listen.Run);
            this->listen.connected = 1;
            thread.launch();
        }

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
                            if(e->cInput != NULL && abs(e->cState->state) != Animations::STICKMAN_DAMAGE && abs(e->cState->state) != Animations::STICKMAN_DIE) {
                                e->cState->toUpdate = -1 * Animations::STICKMAN_RUN;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL && abs(e->cState->state) != Animations::STICKMAN_DAMAGE && abs(e->cState->state != Animations::STICKMAN_DIE)) {
                                e->cState->toUpdate = Animations::STICKMAN_RUN;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::F:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL && abs(e->cState->state) != Animations::STICKMAN_DAMAGE && abs(e->cState->state) != Animations::STICKMAN_DIE) {
                                e->cState->toUpdate = Animations::STICKMAN_PUNCH * e->cAnimation->invert;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::Space:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL && abs(e->cState->state) != Animations::STICKMAN_DAMAGE && abs(e->cState->state) != Animations::STICKMAN_DIE) {
                                e->cState->toUpdate = Animations::STICKMAN_JUMP * e->cAnimation->invert;
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
                                if(e->cState->state == -1) e->cState->toUpdate = Animations::STICKMAN_IDLE;
                                break;
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        for(auto e : m_entities.getEntities()) {
                            if(e->cInput != NULL) {
                                if(e->cState->state == 1) e->cState->toUpdate = Animations::STICKMAN_IDLE;
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

void Engine::update() {


    // preUpdate
    for(auto e : m_entities.getEntities()) {
        if(e->tag() == skeletalTag && e->cInput == NULL && e->cState->state != Animations::STICKMAN_DIE) {
            CState tempState = this->listen.get_state();
            e->cState->state = tempState.state;
            // e->cState->lastFrameState = tempState.lastFrameState;
            e->cTransform->pos = tempState.position;
            e->cState->toUpdate = tempState.toUpdate;
            e->cHealth->HP = tempState.hp;
        }
        
        if(e->cState != NULL && e->cState->toUpdate != e->cState->INF) e->cState->update();
    }

    // updating states
    for(auto e : m_entities.getEntities()) {
        if(e->cState != NULL) {
            
            if(e->cState->state != e->cState->lastFrameState && abs(e->cState->state) != e->cState->INF) {
                int in = 1;
                if(e->cState->state) in = (e->cState->state / abs(e->cState->state));

                if(e->cState->state == Animations::STICKMAN_IDLE) e->cTransform->velocity.x = 0;
                else if( abs(e->cState->state) == Animations::STICKMAN_RUN) e->cTransform->velocity.x = in * 7.0;
                else if( abs(e->cState->state) == Animations::STICKMAN_PUNCH) e->cTransform->velocity.x = 0;
                else if( abs(e->cState->state) == Animations::STICKMAN_JUMP) {
                    e->cTransform->velocity.y = -18;
                    e->cState->lastState = e->cState->lastFrameState;
                }
                else e->cTransform->velocity.x = 0;

                e->cAnimation->setAnimation(this->m_resources.animations[abs(e->cState->state)], (e->cState->state / (abs(e->cState->state) + (e->cState->state == Animations::STICKMAN_IDLE))) - (e->cAnimation->invert / abs(e->cAnimation->invert)) * (e->cState->state != Animations::STICKMAN_IDLE));
            }
        }
    }

    // update movements
    for(auto e : m_entities.getEntities()) {
        if(e->cTransform != NULL) {
            e->cTransform->velocity += e->cTransform->gravity;            
            e->cTransform->pos += e->cTransform->velocity;

            this->moveAll(e, e->cTransform->pos);
        }
    }

    // update animations
    for(auto e : m_entities.getEntities()) {
        if(e->cAnimation != NULL) {

            e->cAnimation->playAnimation(e->cAnimation->moves, *e->cBones, e->cState);

            if(e->cAnimation->forceFrameOut == 0) {
                if(abs(e->cState->state) == Animations::STICKMAN_DIE) e->cState->toUpdate = -e->cState->INF;
                else e->cState->toUpdate = Animations::STICKMAN_IDLE;
            }
        }
    }

    // check for dead stickman 
    for(auto e : m_entities.getEntities(skeletalTag)) {
        if(e->cState->state == -e->cState->INF) e->destroy();

        if(e->cHealth->HP <= 0 && abs(e->cState->state) != Animations::STICKMAN_DIE) {
            e->cState->toUpdate = Animations::STICKMAN_DIE * e->cAnimation->invert;
        }
    }

    // update sounds

    // late update
    for(auto e : m_entities.getEntities()) {
        if(e->cState != NULL) {
            e->cState->lastFrameState = e->cState->state;
            if(e->cInput != NULL) {
                e->cState->position = e->cTransform->pos;
                e->cState->hp = e->cHealth->HP;
                this->listen.set_sending_state(*e->cState);
            }
        }
    }
}

bool checkRectangularCollision(sf::RectangleShape &rect1, sf::RectangleShape &rect2) {
    sf::FloatRect bounds1 = rect1.getGlobalBounds();
    sf::FloatRect bounds2 = rect2.getGlobalBounds();

    return bounds1.intersects(bounds2);
}

bool checkPointRectangleCollision(sf::RectangleShape &rect, sf::Vector2f &p) {
    sf::FloatRect bounds = rect.getGlobalBounds();
    return bounds.contains(p);
}

int checkScreenCollision(sf::RectangleShape &rect, sf::RenderWindow &window) {
    if(rect.getPosition().x <= rect.getGlobalBounds().width) return 1;
    if(rect.getPosition().y <= rect.getGlobalBounds().height) return 2;
    if(rect.getPosition().x + rect.getGlobalBounds().width >= window.getSize().x) return 3;
    if(rect.getPosition().y + rect.getGlobalBounds().height >= window.getSize().y) return 4;
    return 0;
}

void Engine::checkCollisions(sf::RenderWindow &window) {
    // no collision between characters when no combat


    // collision is between characters and tiles
    for(auto stickman : m_entities.getEntities(skeletalTag)) {
        bool isCollision = false;
        for(auto tile : m_entities.getEntities(tileTag)) {
            if(stickman->cCollision.size() == 0) continue;
            bool headCollided = checkRectangularCollision(stickman->cCollision[0]->boundingBox, tile->cCollision[0]->boundingBox),
                 bodyCollided = checkRectangularCollision(stickman->cCollision[1]->boundingBox, tile->cCollision[0]->boundingBox),
                 feetCollided = checkRectangularCollision(stickman->cCollision[2]->boundingBox, tile->cCollision[0]->boundingBox);

            if(feetCollided && !headCollided && !bodyCollided) {
                stickman->cTransform->pos.y += adjustPosition(stickman->cCollision[2]->boundingBox, tile->cCollision[0]->boundingBox).y;
                this->moveAll(stickman, stickman->cTransform->pos);

                stickman->cTransform->gravity = {0, 0};
                stickman->cTransform->velocity.y = 0;
                isCollision = true;

                if( abs(stickman->cState->state) == Animations::STICKMAN_JUMP) {
                    stickman->cState->toUpdate = abs(stickman->cState->lastState) * stickman->cAnimation->invert;
                }
            }

            if(!feetCollided && !bodyCollided && headCollided) {
                stickman->cTransform->pos.y += adjustPosition(stickman->cCollision[0]->boundingBox, tile->cCollision[0]->boundingBox).y;
                this->moveAll(stickman, stickman->cTransform->pos);

                stickman->cTransform->velocity.y = 0;
                isCollision = true;
            }

            if( (int)feetCollided + (int)headCollided + (int)bodyCollided > 1 ) {
                stickman->cTransform->pos.x += adjustPosition(stickman->cCollision[2]->boundingBox, tile->cCollision[0]->boundingBox).x;
                this->moveAll(stickman, stickman->cTransform->pos);
            }
        }

        if(!isCollision) stickman->cTransform->gravity = {0, 1};
    }

    // collision between two characters at least one of them is hitting 
    for(auto stickman1 : m_entities.getEntities(skeletalTag)) {
        for(auto stickman2 : m_entities.getEntities(skeletalTag)) {
            if(stickman1->id() == stickman2->id()) continue;

            if(abs(stickman1->cState->state) == Animations::STICKMAN_PUNCH && abs(stickman2->cState->state) != Animations::STICKMAN_DAMAGE && abs(stickman2->cState->state) != Animations::STICKMAN_DIE) {
                for(int i = 0;i < (int)stickman2->cCollision.size();i++) {
                    if(checkPointRectangleCollision(stickman2->cCollision[i]->boundingBox, stickman1->cBones->bones[STICKPARTS::RIGHT_HAND].p2)) {
                        stickman2->cState->toUpdate = -1 * Animations::STICKMAN_DAMAGE * stickman1->cAnimation->invert;
                        stickman2->cHealth->updateHealth();
                        break;
                    }
                }
            }
        }
    }

    // collision between characters and the screen bounds
    for(auto stickman: m_entities.getEntities(skeletalTag)) {
        if(checkScreenCollision(stickman->cCollision[1]->boundingBox, window) ){
            stickman->cTransform->pos.x = stickman->cCollision[1]->boundingBox.getGlobalBounds().width;
            this->moveAll(stickman, stickman->cTransform->pos);
        }
        else if(checkScreenCollision(stickman->cCollision[1]->boundingBox, window) ){
            stickman->cTransform->pos.x = window.getSize().x - stickman->cCollision[1]->boundingBox.getGlobalBounds().width;
            this->moveAll(stickman, stickman->cTransform->pos);
        }
        else if(checkScreenCollision(stickman->cCollision[2]->boundingBox, window) ){
            stickman->cTransform->pos.y = window.getSize().y - stickman->cCollision[2]->boundingBox.getGlobalBounds().height;
            this->moveAll(stickman, stickman->cTransform->pos);
        }
    }
}

void Engine::render(sf::RenderWindow &window) {
    window.clear(sf::Color(255, 255, 255, 255));

    window.draw( this->m_resources.backgrounds[this->level.background] );

    for(auto e : m_entities.getEntities(tileTag)) {
        window.draw(e->cTextrue->sprite);
    }

    // for(auto tiles: m_entities.getEntities(tileTag)) {
    //     tiles->cCollision[0]->boundingBox.setOutlineThickness(2);
    //     tiles->cCollision[0]->boundingBox.setOutlineColor(sf::Color::Red);
    //     tiles->cCollision[0]->boundingBox.setFillColor(sf::Color(255, 0, 0, 0));
    //     window.draw(tiles->cCollision[0]->boundingBox);
    // }
    // for(auto &e : m_entities.getEntities()) {
    //     for(auto colissionBox: e->cCollision) {
    //         window.draw(colissionBox->boundingBox);
    //     }
    // }

    // for(auto e : m_entities.getEntities(stickmanTag)) {
    //     window.draw(e->cTextrue->sprite);
    // }


    for(auto &e : m_entities.getEntities(skeletalTag)) {
        for(auto &b : e->cBones->bones) {
            b.draw(window);
        }

        // e->cBones->bones[STICKPARTS::WAIST].draw(window);
        // e->cBones->bones[STICKPARTS::LEFT_LEG].draw(window);
        // e->cBones->bones[STICKPARTS::RIGHT_LEG].draw(window);
        // e->cBones->bones[STICKPARTS::LEFT_FOOT].draw(window);
        // e->cBones->bones[STICKPARTS::RIGHT_FOOT].draw(window);

        if(e->cHealth != NULL) {
            window.draw(e->cHealth->healthBar);
            window.draw(e->cHealth->health);
        }
    }


    window.display();
}
