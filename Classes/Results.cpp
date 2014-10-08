#include "HelloWorldScene.h"
#include "Main.h"
#include "Results.h"

USING_NS_CC;

#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey

Scene* Results::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Results::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Results::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //sound
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");

  //stuff
    //X M L
    //score
    CCUserDefault *def=CCUserDefault::sharedUserDefault();
    int _score = def->getIntegerForKey("_SCORE");
    //highscore
    //check whether xml save file exists
    if ( !LoadBooleanFromXML("_IS_EXISTED")){ //if not exist
           SaveBooleanToXML("_IS_EXISTED", true); //create xml absent variable
           SaveIntegerToXML("_HIGHSCORE", 0); //save highscore variable; set to 0
    }
    //handle highscore value
    _highscore = LoadIntegerFromXML("_HIGHSCORE"); //set hs to xml file data
    if(_score > _highscore){ //set hs accordingly
    	_highscore = _score; //set locale highscore to score
    	SaveIntegerToXML("_HIGHSCORE", _highscore); //save xml file with new highscore
    }

    int scoreXOffset;
    int highScoreXOffset;
    if(_score < 10){scoreXOffset = 30;}
    if(_score > 10){scoreXOffset = 40;}
    if(_score > 100){scoreXOffset = 50;}
    if(_highscore < 10){highScoreXOffset = 30;}
    if(_highscore > 10){highScoreXOffset = 40;}
    if(_highscore > 100){highScoreXOffset = 50;}

  //score label
    auto scoreLabel = LabelTTF::create("Score: ", "galaxy.ttf", 100);
    scoreLabel->setPosition(Point(visibleSize.width/2 - scoreLabel->getContentSize().width/2 - scoreXOffset, origin.y + visibleSize.height - scoreLabel->getContentSize().height + 1100));
    scoreLabel->setAnchorPoint(Point(0.0f, 12.0f));
    this->addChild(scoreLabel);
    scoreLabel->setString(ccsf("Score: %d", _score));

  //highscore label
    auto highScoreLabel = LabelTTF::create("HighScore: ", "galaxy.ttf", 55);
    highScoreLabel->setPosition(Point(visibleSize.width/2 - highScoreLabel->getContentSize().width/2 - highScoreXOffset, origin.y + visibleSize.height - highScoreLabel->getContentSize().height + 700));
    highScoreLabel->setAnchorPoint(Point(0.0f, 18.0f));
    this->addChild(highScoreLabel);
    highScoreLabel->setString(ccsf("Highscore: %d", _highscore));

  //start button menu item
  auto start = MenuItemImage::create("go_normal.png", "go_press.png", CC_CALLBACK_1(Results::startButton, this));
  start->setPosition(Point(visibleSize.width/2, (visibleSize.height/2.2) - 30));
  start->setScale(visibleSize.width/9*.01);

  //menu
  auto *menu = Menu::create(start, NULL);
  menu->setPosition(Point(0,0));
  this->addChild(menu);

return true;
}

void Results::startButton(cocos2d::Ref *pSender){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	auto scene = Main::createScene(); //new scene instance of class to push
	Director::getInstance()->pushScene(TransitionFade::create(1, scene)); //push the created scene
}
