#ifndef __MAIN_H__
#define __MAIN_H__

#include "cocos2d.h"
#include <base/CCUserDefault.h>

class Main : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(Main);

    //Main stuff
    cocos2d::Sprite *player; //player
    cocos2d::Sprite *enemy1; //enemy1
    cocos2d::Sprite *enemy2; //enemy2
    cocos2d::Sprite *enemy3; //enemy3

    bool alive;

    float randX;

    int score;

    cocos2d::LabelTTF *scoreLabel;

    const char *_SCORE;

    void update(float dt); //frame update 60/s stable

    void OnAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);

    float getDistance(float enemyx, float enemyy, float playerx, float playery);

    double hps;

    cocos2d::CCParticleSystemQuad *emitter;

};

#endif // __MAIN_H__
