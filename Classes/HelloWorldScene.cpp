#include "HelloWorldScene.h"
#include "Main.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //logo menu item
    auto logo = MenuItemImage::create("logo.png", "logo.png", CC_CALLBACK_1(HelloWorld::logoButton, this));
    logo->setPosition(Point(visibleSize.width/2, (visibleSize.height/1.6) * 1));
    logo->setScale(visibleSize.width/6*.01);

    //start button menu item
    auto start = MenuItemImage::create("go_normal.png", "go_press.png", CC_CALLBACK_1(HelloWorld::startButton, this));
    start->setPosition(Point(visibleSize.width/2, (visibleSize.height/2.2) - 30));
    start->setScale(visibleSize.width/9*.01);

    //menu
    auto *menu = Menu::create(logo, start, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    //sound
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
    return true;
}


void HelloWorld::startButton(cocos2d::Ref *pSender){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	auto scene = Main::createScene(); //new scene instance of class to push
	Director::getInstance()->pushScene(TransitionFade::create(1, scene)); //push the created scene
}
void HelloWorld::logoButton(cocos2d::Ref *pSender){

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
