#ifndef __RESULTS_H__
#define __RESULTS_H__

#include "cocos2d.h"

class Results : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(Results);

    //stuff
    void startButton(Ref *pSender);

    int _highscore;

};

#endif // __RESULTS_H__
